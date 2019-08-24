// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "pixel.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , scene_(scene)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
  double d = (width_/2.0f)/tan((scene_.camera_->fieldOfView_/2.0f)*M_PI/180);

  /* Kameratransformation (Seite 40)   */

  glm::vec3 n = glm::normalize(scene_.camera_->direction_);
  glm::vec3 up = scene_.camera_->up_;
  glm::vec3 u = glm::normalize(glm::cross(n,up));
  glm::vec3 v = glm::normalize(glm::cross(u,n));

  // scene_.camera_->rotationMat_ = glm::mat4{glm::vec4{u,0.0f},glm::vec4{v,0.0f},glm::vec4{-n,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}};

  for (int x = 0; x < width_; ++x) {
    
    for(int y = 0; y < height_; ++y) {
      
      Pixel p(x,y);

      /* creating the camera ray */
      glm::vec3 origin = scene_.camera_->pos_;
      glm::vec3 direction = glm::vec3{x-(0.5*width_),y-(0.5*height_),-d}; //d

      /* changing the direction depending on the adressed pixel */


      Ray ray{origin, glm::normalize(direction)};
      /**
       * not yet implemented 
       * ray = transformRay(s.camera->rotMat, ray);
       */

      /**
       * Intersecion and color calculation
       */
      hitpoint hit = scene_.root_comp_->intersect(ray);

      if(hit.hit_) {
        Color current = calculate_color(hit, 2);
        p.color = current;
      } else {
        p.color = scene_.ambiente_->col_;
      }
      p.color = tonemapping(p.color);
      write(p);
    }
  }
  // std::size_t const checker_pattern_size = 20;

  // for (unsigned y = 0; y < height_; ++y) {
  //   for (unsigned x = 0; x < width_; ++x) {
  //     Pixel p(x,y);
  //     if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
  //       p.color = Color(0.0, 1.0, float(x)/height_);
  //     } else {
  //       p.color = Color(1.0, 0.0, float(y)/width_);
  //     }

  //     write(p);
  //   }
  // }
  // ppm_.save(filename_);
}

Color Renderer::calculate_color(hitpoint const& hit, int counter){
  Color color {0.0f,0.0f,0.0f};
  Color ambiente = calculate_ambiente(hit);

  for(auto l : scene_.light_){
    color += calculate_light(hit, l);
  }
  return color+ambiente;
}

Color Renderer::tonemapping(Color const& clr){
  Color color{0.0f,0.0f,0.0f};
  color.r = clr.r/clr.r+1;
  color.b = clr.b/clr.b+1;
  color.g = clr.g/clr.g+1;
  return color;
}

Color Renderer::calculate_light(hitpoint const& hit, std::shared_ptr<Light> light){
  Ray shape_to_light {hit.hitpoint_, glm::normalize(light->pos_-hit.hitpoint_)};
  hitpoint h = scene_.root_comp_->intersect(shape_to_light);
  Color color{0.0f,0.0f,0.0f};

  if(!(h.hit_) || h.hit_){
    
    color = hit.material_->ks; //Farberechnung fehlt
  }
  return color;
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

Ray transformRay(Ray const& ray, glm::mat4 m){
  glm::vec4 origin {ray.origin, 1.0f};
  glm::vec4 direction {ray.direction, 0.0f};

  origin = m * origin;
  direction = m * direction;

  Ray value{{origin.x, origin.y, origin.z},{direction.x, direction.y, direction.z}};
  return value;
}

Color Renderer::calculate_ambiente(hitpoint const& hit) {
  Color ambiente = scene_.ambiente_->col_;
  Color ka = hit.material_->ka;
  
  return ambiente*ka;
}

Color Renderer::calculate_diffuse(hitpoint const& hit, std::shared_ptr<Light> light) {
  Color Ip = light->col_*light->brightness_;
  glm::vec3 to_light = glm::normalize(light->pos_-hit.hitpoint_);
  float aux = glm::dot(to_light,glm::normalize(hit.normal_));
  return Ip*hit.material_->kd*aux;
}
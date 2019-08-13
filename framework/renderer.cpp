// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "scene.hpp"
#include "pixel.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render(Scene const& s, int frames)
{
  double d = (width_/2)/tan((s.camera_->fieldOfView_/2)*M_PI/180);

  /* Kameratransformation (Setie 40)   */

  glm::vec3 n = glm::normalize(s.camera_->direction_);
  glm::vec3 up = s.camera_->up_;
  glm::vec3 u = glm::normalize(glm::cross(n,up));
  glm::vec3 v = glm::normalize(glm::cross(u,n));

  s.camera_->rotationMat_ = glm::mat4{glm::vec4{u,0.0f},glm::vec4{v,0.0f},glm::vec4{-n,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}};

  for (int x = 0; x < width_; ++x) {
    
    for(int y = 0; y < height_; ++y) {
      
      Pixel p(x,y);

      /* creating the camera ray */
      glm::vec3 origin = s.camera_->pos_;
      glm::vec3 direction = glm::normalize(s.camera_->direction_);

      /* changing the direction depending on the adressed pixel */
      direction += glm::vec3{x-(0.5*width_),y-(0.0*height_),-d};

      Ray ray{origin, glm::normalize(direction)};
      /**
       * not yet implemented 
       * ray = transformRay(s.camera->rotMat, ray);
       */

      /**
       * Intersecion and color calculation
       */
      // bool hit = s.root_comp_->intersect(ray).hit_;

      // if(hit) {
      //   Color current = calculate_color();
      //   p.color = current;
      // }


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

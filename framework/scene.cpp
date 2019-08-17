#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include "Material.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "pyramide.hpp"

std::shared_ptr<Material> Scene::search_vec(std::string const& s){
    for( std::shared_ptr<Material> m : vec_mat_){
        if(m->name_ == s){
            return m;
        }
    }
}
// std::shared_ptr<Material> Scene::search_set(std::string s){
//     std::shared_ptr<Material> f;
//     f->name_ = s;
//     set_mat_.find(f->name_);
// }
std::shared_ptr<Material> Scene::search_map(std::string const& s){
  auto it = map_mat_.find(s);
  if (it != map_mat_.end()){
    return it->second;
  }
  std::shared_ptr<Material> ptr(nullptr);
  return ptr;
}
Scene creatematerial(std::string const& s){
    std::string line_buffer;
    std::ifstream in_scene_file;
    Scene scene;

    in_scene_file.open(s);

    while (std::getline(in_scene_file, line_buffer))
    {
      std::istringstream line_string_stream(line_buffer);
      std::string identifier;
      line_string_stream >> identifier;

      if("define" == identifier)
      {
        if("material" == identifier)
          {
              std::string material_name;
              line_string_stream >> material_name;

              float ka_r,ka_g,ka_b,kd_r,kd_g,kd_b,ks_r,ks_g,ks_b,flt;
              line_string_stream >> ka_r;
              line_string_stream >> ka_g;
              line_string_stream >> ka_b;

              line_string_stream >> kd_r;
              line_string_stream >> kd_g;
              line_string_stream >> kd_b;

              line_string_stream >> ks_r;
              line_string_stream >> ks_g;
              line_string_stream >> ks_b;

              line_string_stream >> flt;            

              Material mat{material_name,{ka_r,ka_g,ka_b},{kd_r,kd_g,kd_b},{ks_r,ks_g,ks_b},flt};
              auto material = std::make_shared<Material>(mat);
              std::cout << mat << std::endl;
              scene.vec_mat_.push_back(material);
              scene.set_mat_.insert(material);
              scene.map_mat_.emplace(material_name,material);
          }
      }
    }
    in_scene_file.close();
    return scene;
}

Scene read_SDF(std::string const& s) {
    std::string line_buffer;
    std::ifstream in_scene_file;
    Scene scene;

    in_scene_file.open(s);

    while (std::getline(in_scene_file, line_buffer))
    {
      std::istringstream line_string_stream(line_buffer);
      std::string identifier;
      line_string_stream >> identifier;

      if("define" == identifier)
      {
          line_string_stream >> identifier;
          if("sphere" == identifier){
            std::string sphere_name;
            line_string_stream >> sphere_name;

            float r;
            glm::vec3 c;
            std::string mat;
            std::shared_ptr<Material> m;

            line_string_stream >> r;

            line_string_stream >> c.x;
            line_string_stream >> c.y;
            line_string_stream >> c.z;

            line_string_stream >> mat;
            auto m = scene.search_vec(mat);

            Sphere sph{c, r, m, sphere_name};
            std::shared_ptr<Shape> ptr_sphere = std::make_shared<Box>(sph);
            /**
             * Wie fügen wir die Objekte den root_comp hinzu? 
            */

          }

          if("box" == identifier){
            std::string box_name;
            line_string_stream >> box_name;

            glm::vec3 min;
            glm::vec3 max;
            std::string mat;
            std::shared_ptr<Material> m;

            line_string_stream >> min.x;
            line_string_stream >> min.y;
            line_string_stream >> min.z;

            line_string_stream >> max.x;
            line_string_stream >> max.y;
            line_string_stream >> max.z;

            line_string_stream >> mat;
            auto m = scene.search_vec(mat);

            Box box{min, max, box_name, m};

            std::shared_ptr<Shape> ptr_box = std::make_shared<Box>(box);
            /**
             * Wie fügen wir die Objekte den root_comp hinzu? 
            */
          }

          if("light" == identifier){
            std::string light_name;
            line_string_stream >> light_name;

            float clr_r, clr_g, clr_b;
            glm::vec3 pos;
            double brightness;

            line_string_stream >> clr_r;
            line_string_stream >> clr_g;
            line_string_stream >> clr_b;

            line_string_stream >> pos.x;
            line_string_stream >> pos.y;
            line_string_stream >> pos.z;

            line_string_stream >> brightness;

            Light light{light_name, pos, {clr_r, clr_g, clr_b}, brightness};
            auto l = std::make_shared<Light>(light);
            scene.light_.push_back(l);
          }
          if("pyramide" == identifier){
            std::string pyramide_name;
            glm::vec3 pmin, pmax, apex;
            float side, height;
            std::string mat;
            std::shared_ptr<Material> m;

            line_string_stream >> pmin.x;
            line_string_stream >> pmin.y;
            line_string_stream >> pmin.z;

            line_string_stream >> pmax.x;
            line_string_stream >> pmax.y;
            line_string_stream >> pmax.z;

            line_string_stream >> apex.x;
            line_string_stream >> apex.y;
            line_string_stream >> apex.z;

            line_string_stream >> side;

            line_string_stream >> height;

            m = scene.search_vec(mat);

            Pyramide pyramide{pmin, side, height, pyramide_name, m};
            
          }

          if("camera" == identifier){
            std::string camera_name;
            glm::vec3 pos,direction,up;
            unsigned int fieldOfView;

            line_string_stream >> camera_name;

            line_string_stream >> pos.x;
            line_string_stream >> pos.y;
            line_string_stream >> pos.z;
            
            line_string_stream >> direction.x;
            line_string_stream >> direction.y;
            line_string_stream >> direction.z;
            
            line_string_stream >> up.x;
            line_string_stream >> up.y;
            line_string_stream >> up.z;
            
            line_string_stream >> fieldOfView;

            Camera camera(camera_name,pos,direction,up,fieldOfView);
            scene.camera_ = std::make_shared<Camera>(camera);
          }

          if("ambiente" == identifier) {
            std::string ambiente_name;

            float clr_r, clr_g, clr_b;

            line_string_stream >> ambiente_name;

            line_string_stream >> clr_r;
            line_string_stream >> clr_g;
            line_string_stream >> clr_b;

            Ambiente ambiente{{clr_r, clr_g, clr_b}};
            scene.ambiente_ = std::make_shared<Ambiente>(ambiente);
          }

    in_scene_file.close();
    return scene;
  }
}

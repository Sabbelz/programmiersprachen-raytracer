#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include "Material.hpp"
#include "scene.hpp"

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
Scene creatematerial(std::string const& s) {
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


static void read_SDF(std::string const& s, Scene& sc){
    std::ifstream i;
    i.open(s);
    if(!i.is_open()){
        std::cout << "Error occured while opening the given file!" << std::endl;
    } else{
        std::cout << "File successfully opened" << std::endl;
        std::string line;
        std::map<std::string, std::shared_ptr<Shape>> map_shape;
        std::map<std::string, std::shared_ptr<Composite>> map_composite;
        std::shared_ptr<Composite> comp_obj = nullptr;
        while(std::getline(i,line)){
            deserializeObjects(sc, line, map_shape, map_composite, comp_obj);
        }
        if(sc.root_comp_ != nullptr && comp_obj != nullptr){
            sc.root_comp_->add(comp_obj);
        }
        else if(sc.root_comp_ == nullptr){
            sc.root_comp_ = comp_obj;
        }
        sc.root_comp_->creatBoundingBox();
        std::cout << "Scene successfully loaded" << std::endl;
    }
}
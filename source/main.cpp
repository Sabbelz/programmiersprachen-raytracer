#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include "Material.hpp"

int main(int argc, char** argv) {
    std::string line_buffer;
    std::ifstream in_scene_file(argv[1]);

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
              std::cout << mat << std::endl;
          }
      }
    }

}
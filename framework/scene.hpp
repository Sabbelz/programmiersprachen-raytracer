#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include "Material.hpp"
#include "shape.hpp"
#include "hitpoint.hpp"
#include "ambiente.hpp"
#include "camera.hpp"
#include "light.hpp"

struct Scene{

    std::vector<std::shared_ptr<Material>> vec_mat_;
    std::set<std::shared_ptr<Material>> set_mat_;
    std::map<std::string, std::shared_ptr<Material>> map_mat_;
    std::shared_ptr<Ambiente> ambiente_;
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Composite> root_comp_;

    std::shared_ptr<Material> search_vec(std::string s);
    std::shared_ptr<Material> search_set(std::string s);
    std::shared_ptr<Material> search_map(std::string s);
};

    Scene creatematerial(std::string s);
    static void read_SDF(std::string s, Scene& scene);

#endif
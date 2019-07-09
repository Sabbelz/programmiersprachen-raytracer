#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include <set>
#include <map>
#include "Material.hpp"
#include "shape.hpp"
#include "hitpoint.hpp"

struct Scene{

    std::vector<std::shared_ptr<Material>> vec_mat_;
    std::set<std::shared_ptr<Material>> set_mat_;
    std::map<std::string, std::shared_ptr<Material>> map_mat_;
};

#endif
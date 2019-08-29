#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "Material.hpp"
#include "shape.hpp"
#include "hitpoint.hpp"
#include "ambiente.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "composite.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "pyramide.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "triangle.hpp"


struct Scene{

    std::vector<std::shared_ptr<Material>> vec_mat_;
    std::set<std::shared_ptr<Material>> set_mat_;
    std::map<std::string, std::shared_ptr<Material>> map_mat_;

    std::shared_ptr<Ambiente> ambiente_;
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Shape> root_comp_;
    std::vector<std::shared_ptr<Light>> light_;

    std::shared_ptr<Material> search_vec(std::string const& s);
    std::shared_ptr<Material> search_set(std::string const& s);
    std::shared_ptr<Material> search_map(std::string const& s);
};

    Scene creatematerial(std::string const& s);
    Scene read_SDF(std::string const& s);

#endif
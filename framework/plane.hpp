#ifndef PLANE_HPP
#define PLANE_HPP
#include <glm/vec3.hpp>

struct Plane{
    glm::vec3 normal_;
    glm::vec3 origin_;
};

#endif
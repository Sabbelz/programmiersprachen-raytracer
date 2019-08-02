#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>

struct Camera{
    glm::vec3 pos_;
    glm::vec3 dir_;
    std::string name_;
};
#endif
#ifndef HITPOINT_CPP
#define HITPOINT_CPP
#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"
#include <memory>
#include "Material.hpp"

struct hitpoint{
    bool hit_ = false;
    float distance_ = __FLT_MAX__;
    std::string name_ = "missed";
    std::shared_ptr<Material> material_;
    glm::vec3 direction_;
    glm::vec3 hitpoint_;

};

#endif
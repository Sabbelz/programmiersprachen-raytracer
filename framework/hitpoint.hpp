#ifndef HITPOINT_CPP
#define HITPOINT_CPP
#include <string>
#include <glm/vec3.hpp>

struct hitpoint{
    bool hit_ = false;
    float distance_ = __FLT_MAX__;
    std::string name_ = "missed";
    glm::vec3 color_ {0.0f};
    glm::vec3 direction_;

};

#endif
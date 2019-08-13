#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <string>
#include <cmath>
#include "imageplane.hpp"

struct Camera{

    Camera(std::string name, glm::vec3 pos, glm::vec3 direction, glm::vec3 up, unsigned int fieldOfView):
    name_(name), pos_(pos), direction_(direction), up_(up), fieldOfView_(fieldOfView){
    rotationMat_ = glm::mat4x4{
        glm::vec4{1.0f,0.0f,0.0f,0.0f},
        glm::vec4{0.0f,1.0f,0.0f,0.0f},
        glm::vec4{0.0f,0.0f,1.0f,0.0f},
        glm::vec4{0.0f,0.0f,0.0f,1.0f}};
    }
    
    friend std::ostream& operator<<(std::ostream& os, Camera const& cam){
        os << "Name: " << cam.name_
            << "Position: " << cam.pos_.x << ", " << cam.pos_.y << ", " << cam.pos_.z
            << "Field of view: " << cam.fieldOfView_ << std::endl;
        return os;
    }

    std::string name_;
    glm::vec3 pos_;
    glm::vec3 direction_; //normalized
    glm::vec3 up_;
    unsigned int fieldOfView_;
    glm::mat4x4 rotationMat_;
};

#endif

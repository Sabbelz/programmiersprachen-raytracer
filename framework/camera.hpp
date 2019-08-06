#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <string>
#include <cmath>
#include "imageplane.hpp"

class Camera{
    public:

    Camera();
    Camera(std::string name, glm::vec3 pos, glm::vec3 direction, float xAngle, float yAngle):
    name_(name), pos_(pos), direction_(direction), xAngle_(xAngle), yAngle_(yAngle){
    mat_ = glm::mat4x4{
        glm::vec4{1.0f,0.0f,0.0f,0.0f},
        glm::vec4{0.0f,1.0f,0.0f,0.0f},
        glm::vec4{0.0f,0.0f,1.0f,0.0f},
        glm::vec4{0.0f,0.0f,0.0f,1.0f}};
    }
    ~Camera();

    friend std::ostream& operator<<(std::ostream& os, Camera const& cam){
        os << "Name: " << cam.name_
            << "Position: " << cam.pos_.x << ", " << cam.pos_.y << ", " << cam.pos_.z
            << "x Angle: " << cam.xAngle_
            << "y Angle: " << cam.yAngle_ << std::endl;
        return os;
    }

    private:

    std::string name_;
    glm::vec3 pos_;
    glm::vec3 direction_; //normalized
    float xAngle_; 
    float yAngle_;
    float d_; //distance to imageplane
    glm::mat4x4 mat_;
    Imageplane imageplane;

};

#endif

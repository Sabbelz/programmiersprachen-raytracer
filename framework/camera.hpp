#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <cmath>
#include "imageplane.hpp"

class Camera{
    public:
    Camera();
    Camera(std::string name, glm::vec3 pos, glm::vec3 direction, float xAngle, float yAngle);

    private:
    std::string name_;
    glm::vec3 pos_;
    glm::vec3 direction_; //normalized
    float xAngle_; 
    float yAngle_;
    float d_; //distance to imageplane
    Imageplane imageplane;

};

#endif
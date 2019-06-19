#include "box.hpp"

Box::Box():
max_{0.0f},
min_{0.0f}{}

Box::Box(glm::vec3 const& max, glm::vec3 const& min):
max_{max},
min_{min}{}

Box::Box(glm::vec3 const& max, glm::vec3 const& min, std::string const& name, glm::vec3 const& color):
Shape{color, name},
max_{max},
min_{min}{}

float Box::area() const{
    float a = max_.x - min_.y;
    float b = max_.y - min_.x;
    float c = max_.z - min_.z;

    return abs(2*(a*b+b*c+a*c));

}

float Box::volume() const{
    float a = max_.x - min_.y;
    float b = max_.y - min_.x;
    float c = max_.z - min_.z;

    return abs(a*b*c);
}
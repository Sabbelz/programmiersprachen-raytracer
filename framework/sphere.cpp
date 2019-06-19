#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
Shape{},
center_{0.0f},
radius_{0.0f}{}

Sphere::Sphere(glm::vec3 const& center, float radius):
Shape{},
center_{center},
radius_{abs(radius)}{}

Sphere::Sphere(glm::vec3 const& center, float radius, glm::vec3 const& color, std::string const& name):
Shape{color, name},
center_{center},
radius_{abs(radius)}{}


float Sphere::area() const{
    return (4* M_PI * radius_ * radius_);
}

float Sphere::volume() const{
    return (4.f/3.f * M_PI * pow(radius_,3));
}
std::ostream& Sphere::print(std::ostream& os) const{
    Shape::print(os);
    return os << "Center: " << center_.x << center_.y << center_.z
              << " Radius: " << radius_ << std::endl;
}
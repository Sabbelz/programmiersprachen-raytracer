#include "Cylinder.hpp"

Cylinder::Cylinder():
    Shape{},
    center_{0.0f},
    height_{0.0f},
    radius_{0.0f}
{}

Cylinder::Cylinder(glm::vec3 const& center, float height, float radius):
    Shape{},
    center_{center},
    height_{height},
    radius_{radius}
{}

Cylinder::Cylinder(glm::vec3 const& center, float height, float radius, std::string const& name, std::shared_ptr<Material> material):
    Shape{material, name},
    center_{center},
    height_{height},
    radius_{radius}
{}

Cylinder::~Cylinder(){}

float Cylinder::area() const{
    float area_o = (2*M_PI*radius_*height_) + (2*M_PI*radius_*radius_ + 2*M_PI*radius_*height_);

    return area_o;

}

float Cylinder::volume() const{
    float volume = M_PI * radius_ * radius_ * height_;
    return volume;
}

std::ostream& Cylinder::print(std::ostream& os) const{
    Shape::print(os);
    return os << " Center: " << center_.x << center_.y << center_.z
              << " Radius: " << radius_ << " Height: " << height_ << "\n";
}
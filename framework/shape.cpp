#include "shape.hpp"

Shape::Shape():
color_{0.0f},
name_{"default"}{}

Shape::Shape(glm::vec3 const& color, std::string const& name):
color_{color},
name_{name}{}

std::ostream& Shape::print(std::ostream& os) const{
    return os << " Color: " << color_.x
              << color_.y << color_.z 
              << " Name: " << name_ << "\n";  
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}

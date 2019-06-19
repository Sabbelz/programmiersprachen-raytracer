#include "shape.hpp"

Shape::Shape():
color_{0.5f,0.5f,0.5f},
name_{"default"}{std::cout << "Shape constructor used." << std::endl;}

Shape::Shape(Color const& color, std::string const& name):
color_{color},
name_{name}{std::cout << "Shape constructor used." << std::endl;}

std::ostream& Shape::print(std::ostream& os) const{
    return os << " Color: " << color_.r << " "
              << color_.g << " " << color_.b << " "
              << " Name: " << name_ << "\n";  
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}

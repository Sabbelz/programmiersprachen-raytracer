#include "shape.hpp"

Shape::Shape():
material_{},
name_{"default"}{/* std::cout << "Shape constructor used." << std::endl;*/}

Shape::Shape(std::shared_ptr<Material> material, std::string const& name):
material_{material},
name_{name}{/*std::cout << "Shape constructor used." << std::endl;*/}

std::ostream& Shape::print(std::ostream& os) const{
    return os << "Material: " << *material_
              << "Name: " << name_ << "\n";  
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}

#include "shape.hpp"

Shape::Shape():
material_{},
name_{"default"}{
    world_transformation_= glm::mat4x4{glm::vec4{1.0f,0.0f,0.0f,0.0f},glm::vec4{0.0f,1.0f,0.0f,0.0f},glm::vec4{0.0f,0.0f,1.0f,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}};
    world_transformation_inv_ = glm::inverse(world_transformation_);}

Shape::Shape(std::shared_ptr<Material> material, std::string const& name):
material_{material},
name_{name}{
    world_transformation_= glm::mat4x4{glm::vec4{1.0f,0.0f,0.0f,0.0f},glm::vec4{0.0f,1.0f,0.0f,0.0f},glm::vec4{0.0f,0.0f,1.0f,0.0f},glm::vec4{0.0f,0.0f,0.0f,1.0f}};
    world_transformation_inv_ = glm::inverse(world_transformation_);}

std::ostream& Shape::print(std::ostream& os) const{
    return os << "Material: " << *material_
              << "Name: " << name_ << "\n";  
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
}

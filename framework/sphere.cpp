#include "sphere.hpp"
#include "renderer.hpp"
#include <cmath>

Sphere::Sphere():
Shape{},
center_{0.0f},
radius_{0.0f}{/*std::cout << "Sphere constructor used."<<std::endl;*/}

Sphere::Sphere(glm::vec3 const& center, float radius):
Shape{},
center_{center},
radius_{abs(radius)}{/*std::cout << "Sphere constructor used."<<std::endl;*/}

Sphere::Sphere(glm::vec3 const& center, float radius,std::shared_ptr<Material> material, std::string const& name):
Shape{material, name},
center_{center},
radius_{abs(radius)}{/*std::cout << "Sphere constructor used."<<std::endl; */}

Sphere::~Sphere(){}


float Sphere::area() const{
    return (4* M_PI * radius_ * radius_);
}

float Sphere::volume() const{
    return (4.f/3.f * M_PI * pow(radius_,3));
}
std::ostream& Sphere::print(std::ostream& os) const{
    Shape::print(os);
    return os << "Center: {" << center_.x << ";" << center_.y << ";" << center_.z << "}"
              << " Radius: " << radius_ << std::endl;
}

hitpoint Sphere::intersect(Ray const& r) const{
    Ray n = transformRay(r, world_transformation_inv_);
    hitpoint hit{};
    float distance;
    bool washit = glm::intersectRaySphere(n.origin, glm::normalize(n.direction), center_, pow(radius_,2), distance);
    if (washit == true){
        hit.hitpoint_= n.origin + distance*n.direction; 
        hit.normal_ = glm::normalize(hit.hitpoint_ - center_);
        glm::vec4 transformed_point = world_transformation_ * glm::vec4{hit.hitpoint_, 1};
        glm::vec4 transformed_normal = glm::normalize(glm::transpose(world_transformation_inv_)* glm::vec4{hit.normal_,0});
        hit.hitpoint_ = glm::vec3{transformed_point.x, transformed_point.y, transformed_point.z};
        hit.normal_ = glm::vec3{transformed_normal.x, transformed_normal.y, transformed_normal.z};
        hit.hit_= true;
        hit.material_ = material_;
        hit.direction_ = r.direction;
        hit.distance_ = glm::length(hit.hitpoint_ - r.origin);
        hit.name_ = name_;
    }
    return hit;
}
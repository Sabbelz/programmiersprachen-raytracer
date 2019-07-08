#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
Shape{},
center_{0.0f},
radius_{0.0f}{std::cout << "Sphere constructor used."<<std::endl;}

Sphere::Sphere(glm::vec3 const& center, float radius):
Shape{},
center_{center},
radius_{abs(radius)}{std::cout << "Sphere constructor used."<<std::endl;}

Sphere::Sphere(glm::vec3 const& center, float radius,std::shared_ptr<Material> material, std::string const& name):
Shape{material, name},
center_{center},
radius_{abs(radius)}{std::cout << "Sphere constructor used."<<std::endl;}


float Sphere::area() const{
    return (4* M_PI * radius_ * radius_);
}

float Sphere::volume() const{
    return (4.f/3.f * M_PI * pow(radius_,3));
}
std::ostream& Sphere::print(std::ostream& os) const{
    Shape::print(os);
    return os << "Center: " << center_.x << " " << center_.y << " " << center_.z
              << " Radius: " << radius_ << std::endl;
}

hitpoint Sphere::intersect(Ray const& r) const{
    Ray n{r};
    hitpoint hit{};
    float distance;
    bool washit = glm::intersectRaySphere(n.origin, glm::normalize(n.direction), center_, pow(radius_,2), distance);
    if (washit == true){
       hit.hit_= true;
       hit.material_ = material_;
       hit.direction_ = n.direction;
       hit.distance_ = distance;
       hit.name_ = name_;
       hit.hitpoint_ = n.origin + distance*n.direction;
    }
    return hit;
}
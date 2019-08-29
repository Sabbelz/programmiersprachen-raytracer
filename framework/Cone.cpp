#include "Cone.hpp"

Cone::Cone():
    Shape{},
    center_{0.0f},
    height_{0.0f},
    radius_{0.0f}
{}

Cone::Cone(glm::vec3 const& center, float height, float radius):
    Shape{},
    center_{center},
    tip_{center.y + height},
    height_{height},
    radius_{radius}
{}

Cone::Cone(glm::vec3 const& center, float height, float radius, std::string const& name, std::shared_ptr<Material> material):
    Shape{material, name},
    center_{center},
    tip_{center.y + height},
    height_{height},
    radius_{radius}
{}

float Cone::area() const{
    float s = sqrt(height_*height_ + radius_*radius_);
    float area_o = (radius_*radius_ * M_PI) + (radius_ * s * M_PI);

    return area_o;

}

float Cone::volume() const{
    float volume = (1/3)* M_PI * radius_ * radius_ * height_;
    return volume;
}

std::ostream& Cone::print(std::ostream& os) const{
    Shape::print(os);
    return os << "Tip: " << tip_.x << tip_.y << tip_.z
              << " Center: " << center_.x << center_.y << center_.z
              << " Radius: " << radius_ << " Height: " << height_ << "\n";
}

hitpoint Cone::intersect(Ray const& r) const{
    hitpoint h;
    
    return h;
}

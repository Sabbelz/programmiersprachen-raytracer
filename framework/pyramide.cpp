#include "pyramide.hpp"

Pyramide::Pyramide():
Shape{},
pmin_{0.0f},
pmax_{0.0f},
tip_{0.0f},
height_{0.0f},
side_{0.0f}{}

Pyramide::Pyramide(glm::vec3 const& pmin,float side, float height):
Shape{},
height_{height},
side_{side},
pmin_{pmin},
pmax_(pmin.x+height,pmin.y,pmin.z+height)
{
    tip_ = 0.5f * (pmax_ - pmin_);
    tip_.y += height;
}

Pyramide::Pyramide(glm::vec3 const& pmin,float side,float height, std::string const& name, std::shared_ptr<Material> material):
Shape{material, name},
height_{height},
side_{side},
pmin_{pmin},
pmax_(pmin.x+height,pmin.y,pmin.z+height)
{
    tip_ = 0.5f * (pmax_ - pmin_);
    tip_.y += height;
}

float Pyramide::volume() const{
    return (side_*side_*height_)/3.0f;
}

float Pyramide::area() const{
    float base = side_*side_;
    float heigth_rectangle = std::sqrt((0.5f*side_)*(0.5f*side_)+height_*height_);
    return base + 2*side_*heigth_rectangle;
}

std::ostream& Pyramide::print(std::ostream& os) const{
    Shape::print(os);
    return os << "Max: " << pmax_.x << pmax_.y << pmax_.z
              << " Min: " << pmin_.x << pmin_.y << pmin_.z
              << " Tip " << tip_.x << tip_.y << tip_.z
              << " Length of side: " << side_
              << " Heigth: " << height_;
}

hitpoint Pyramide::intersect(Ray const& r)const{
    //NOT IMPLEMENTED YET
    Ray n{r};
    hitpoint hit{};
    bool washit = false;
    float tmin = FLT_MAX;
    return hit;
}
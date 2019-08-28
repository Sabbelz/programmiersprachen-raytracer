#include "Cylinder.hpp"
#include "renderer.hpp"

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
hitpoint Cylinder::intersect(Ray const& r) const{
    Ray n = transformRay(r, world_transformation_inv_);
    hitpoint hit{};
    float distance;
    bool washit = glm::intersectRaySphere(n.origin, glm::normalize(n.direction), center_, pow(radius_,2), distance);
    if (washit == true){
        hit.hitpoint_= n.origin + distance*n.direction; 
        glm::vec4 transformed_point = world_transformation_ * glm::vec4{hit.hitpoint_, 1};

        if(center_.z + radius_ >= transformed_point.z 
            && center_.y >= transformed_point.y 
            && center_.x >= transformed_point.x){

            hit.normal_ = {0.0f,-1.0f,0.0f};
        }
        if(center_.z + radius_>= transformed_point.z 
            && center_.y + height_ >= transformed_point.y 
            && center_.x >= transformed_point.x){

            hit.normal_ = {0.0f,1.0f,0.0f};
            
        } else {
            glm::vec3 hit_center{center_.x, hit.hitpoint_.y, center_.z};
            hit.normal_ = glm::normalize(hit_center - hit.hitpoint_);
        }
       
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
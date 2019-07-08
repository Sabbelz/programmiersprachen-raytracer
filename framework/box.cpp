#include "box.hpp"

Box::Box():
Shape{},
max_{0.0f},
min_{0.0f}{std::cout << "Box constructor used."<<std::endl;}

Box::Box(glm::vec3 const& max, glm::vec3 const& min):
Shape{},
max_{max},
min_{min}{std::cout << "Box constructor used."<<std::endl;}

Box::Box(glm::vec3 const& max, glm::vec3 const& min, std::string const& name, std::shared_ptr<Material> material):
Shape{material, name},
max_{max},
min_{min}{std::cout << "Box constructor used."<<std::endl;}

float Box::area() const{
    float a = max_.x - min_.y;
    float b = max_.y - min_.x;
    float c = max_.z - min_.z;

    return abs(2*(a*b+b*c+a*c));

}

float Box::volume() const{
    float a = max_.x - min_.y;
    float b = max_.y - min_.x;
    float c = max_.z - min_.z;

    return abs(a*b*c);
}

std::ostream& Box::print(std::ostream& os) const{
    Shape::print(os);
    return os << "Max: " << max_.x << max_.y << max_.z
              << " Min: " << min_.x << min_.y << min_.z;
}

hitpoint Box::intersect(Ray const& r)const{
    Ray n{r};
    hitpoint hit{};
    float distance;
    float t = (min_.x-n.origin.x)/n.direction.x;
    glm::vec3 p_x = n.origin + t*n.direction; 
    bool is_inside = false;
    
    if(p_x.x <= max_.x && p_x.y <= max_.y && p_x.x >= min_.x && p_x.y >= min_.y && p_x.z <= max_.z && p_x.z >= min_.z){
        //std::cout << "Der angegebene Punkt liegt innerhalb des Objektes.\n";
        is_inside = true;
    }

    
    if (is_inside == true){
       hit.hit_= true;
       hit.material_ = material_;
       hit.direction_ = n.direction;
       hit.distance_ = distance;
       hit.name_ = name_;
       hit.hitpoint_ = p_x;
    }
    return hit;
}
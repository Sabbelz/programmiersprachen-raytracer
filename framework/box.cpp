#include "box.hpp"
#include "renderer.hpp"

Box::Box():
Shape{},
max_{0.0f},
min_{0.0f}{/*std::cout << "Box constructor used."<<std::endl;*/}

Box::Box(glm::vec3 const& max, glm::vec3 const& min):
Shape{}
{if(max.x > min.x){
    max_= max;
    min_= min;
    }
    else
    {
        min_ = max;
        max_ = min;
    }  
}

Box::Box(glm::vec3 const& max, glm::vec3 const& min, std::string const& name, std::shared_ptr<Material> material):
Shape{material, name}
{if(max.x > min.x){
    max_= max;
    min_= min;
    }
    else
    {
        min_ = max;
        max_ = min;
    }
}

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
    Ray n = transformRay(r, world_transformation_inv_);
    hitpoint hit{};
    bool washit = false;
    float tmin = FLT_MAX;

    float t = (min_.x-n.origin.x)/(glm::normalize(n.direction)).x;
    glm::vec3 p_x = n.origin + t*(glm::normalize(n.direction));
    
    if(p_x.y <= max_.y && p_x.y >= min_.y
    && p_x.z <= max_.z && p_x.z >= min_.z && t > 0){
        //std::cout << "Der angegebene Punkt liegt innerhalb des Objektes.\n";
        washit = true;
        tmin = t;
        hit.hitpoint_ = p_x;
        hit.normal_ = glm::vec3{-1.0f,0.0f,0.0f};
    }

    float t_max_x = (max_.x-n.origin.x)/(glm::normalize(n.direction)).x;
    glm::vec3 p_x2 = n.origin + t_max_x*(glm::normalize(n.direction)); 
    
    if(p_x2.y <= max_.y && p_x2.y >= min_.y
    && p_x2.z <= max_.z && p_x2.z >= min_.z && t_max_x > 0){
        //std::cout << "Der angegebene Punkt liegt innerhalb des Objektes.\n";
        washit = true;
        if(tmin > t_max_x)
        {
            hit.hitpoint_ = p_x2;
            tmin = t_max_x;
            hit.normal_ = glm::vec3{1.0f,0.0f,0.0f};
        }
    }

    float t_min_y = (min_.y-n.origin.y)/(glm::normalize(n.direction)).y;
    glm::vec3 p_y = n.origin + t_min_y*(glm::normalize(n.direction)); 
    
    if(p_y.x <= max_.x && p_y.x >= min_.x
    && p_y.z <= max_.z && p_y.z >= min_.z && t_min_y > 0){
        //std::cout << "Der angegebene Punkt liegt innerhalb des Objektes.\n";
        washit = true;

        if(tmin > t_min_y)
        {
            hit.hitpoint_ = p_y;
            tmin = t_min_y;
            hit.normal_ = glm::vec3{0.0f,-1.0f,0.0f};
        }
    }

    float t_max_y = (max_.y-n.origin.y)/(glm::normalize(n.direction)).y;
    glm::vec3 p_y2 = n.origin + t_max_y*(glm::normalize(n.direction)); 
    
    if(p_y2.x <= max_.x && p_y2.x >= min_.x
    && p_y2.z <= max_.z && p_y2.z >= min_.z && t_max_y > 0){
        //std::cout << "Der angegebene Punkt liegt innerhalb des Objektes.\n";
        washit = true;

        if(tmin > t_max_y)
        {
            hit.hitpoint_ = p_y2;
            tmin = t_max_y;
            hit.normal_ = glm::vec3{0.0f,1.0f,0.0f};
        }
    }
    
    float t_min_z = (min_.z-n.origin.z)/(glm::normalize(n.direction)).z;
    glm::vec3 p_z = n.origin + t_min_z*(glm::normalize(n.direction)); 
    
    if(p_z.y <= max_.y && p_z.y >= min_.y
    && p_z.x <= max_.x && p_z.x >= min_.x && t_min_z > 0){
        //std::cout << "Der angegebene Punkt liegt innerhalb des Objektes.\n";
        washit = true;


        if(tmin > t_min_z)
        {
            hit.hitpoint_ = p_z;
            tmin = t_min_z;
            hit.normal_ = glm::vec3{0.0f,0.0f,-1.0f};
        }
    }

    float t_max_z = (max_.z-n.origin.z)/(glm::normalize(n.direction)).z;
    glm::vec3 p_z2 = n.origin + t_max_z*(glm::normalize(n.direction)); 
    
    if(p_z2.y <= max_.y && p_z2.y >= min_.y
    && p_z2.x <= max_.x && p_z2.x >= min_.x && t_max_z > 0){
        //std::cout << "Der angegebene Punkt liegt innerhalb des Objektes.\n";
        washit = true;


        if(tmin > t_max_z)
        {
            hit.hitpoint_ = p_z2;
            tmin = t_max_z;
            hit.normal_ = glm::vec3{0.0f,0.0f,1.0f};
    
        }
    }

    if (washit == true){
        glm::vec4 transformed_point = world_transformation_ * glm::vec4{hit.hitpoint_, 1};
        glm::vec4 transformed_normal = glm::normalize(glm::transpose(world_transformation_inv_)* glm::vec4{hit.normal_,0});
        hit.hit_= true;
        hit.material_ = material_;
        hit.direction_ = r.direction;
        hit.distance_ = tmin;
        hit.name_ = name_;
        hit.normal_ = glm::vec3{transformed_normal.x, transformed_normal.y, transformed_normal.z};
        hit.hitpoint_ = glm::vec3{transformed_point.x, transformed_point.y, transformed_point.z};
    }
    return hit;
}
#include "triangle.hpp"
#include "renderer.hpp"

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, std::string name ,std::shared_ptr<Material> material) :
    Shape{material,name},
    a_{a},
    b_{b},
    c_{c}{}

Triangle::~Triangle(){}

float Triangle::area() const{
    glm::vec3 ab = b_ - a_;
    glm::vec3 ac = c_ - a_;

    return 0.5f * glm::length(glm::cross(ab,ac));
}

float Triangle::volume() const {
    return -1.0f;
}

std::ostream& Triangle::print(std::ostream& os) const{
    Shape::print(os);
    return os << "A {" << a_.x << "," << a_.y << "," << a_.z << "} \n B {"
            << b_.x << "," << b_.y << "," << b_.z << "} \n C {" 
            << c_.x << "," << c_.y << "," << c_.z << "}"<< std::endl;
}

hitpoint Triangle::intersect(Ray const& r) const{
    hitpoint h;
    Ray ray = transformRay(r,world_transformation_inv_);

    glm::vec3 ab = b_ -a_;
    glm::vec3 ac = c_ - a_;
    glm::vec3 n = glm::cross(ab,ac);

    glm::vec3 q = glm::cross(ray.direction,ac);
    float a = glm::dot(ab,q);
    const float epsilon = 0.0000001;
    
    if(a > -epsilon && a < epsilon) {
        h.hit_ = false;
        return h;
    }

    float f = 1/a;
    glm::vec3 s = ray.origin - a_;
    float u = f * glm::dot(s,q);

    if(u < 0.0f || u > 1.0f) {
        h.hit_ = false;
        return h;
    }

    glm::vec3 w = glm::cross(s,ab);
    float v = f * glm::dot(ray.direction, w);

    if( v < 0.0f ||u + v > 1.0f) {
        h.hit_ = false;
        return h;
    }

    float t = f* glm::dot(ac,w);

    if(t > epsilon) {
        glm::vec3 intersection = ray.origin + t * ray.direction;

        glm::vec4 transformed_intersection = world_transformation_ * glm::vec4{intersection,1};
        glm::vec4 transformed_normal = glm::normalize(world_transformation_ * glm::vec4{glm::normalize(n),0});

        h.hit_ = true;
        h.hitpoint_ = glm::vec3{transformed_intersection.x,transformed_intersection.y,transformed_intersection.z};
        h.normal_ = glm::vec3{transformed_normal.x, transformed_normal.y, transformed_normal.z};
        h.material_=material_;
        h.direction_ = r.direction;
        h.distance_ = glm::length(h.hitpoint_-r.origin);
        h.name_ = name_;
        return h;
    }else{
    h.hit_ = false;
    return h;
    }
}
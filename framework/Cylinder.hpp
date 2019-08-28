#ifndef CYLINDER_HPP
#define CYLINDER_HPP
#include "shape.hpp"

class Cylinder: public Shape{
    public:

    Cylinder();
    Cylinder(glm::vec3 const& center, float height, float radius);
    Cylinder(glm::vec3 const& center, float height, float radius, std::string const& name, std::shared_ptr<Material> material);

    ~Cylinder(){}

    float area() const override;
    float volume() const override;
    hitpoint intersect(Ray const& r) const override;

    std::ostream& print(std::ostream& os) const override;

    private:
    glm::vec3 center_;
    float height_;
    float radius_;

};

#endif
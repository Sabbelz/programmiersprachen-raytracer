#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere: public Shape{
    public:

    Sphere();
    Sphere(glm::vec3 const& center, float radius);
    Sphere(glm::vec3 const& center, float radius, glm::vec3 const& color, std::string const& name);


    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream& os) const override;

    private:
    glm::vec3 center_;
    float radius_;
};

#endif
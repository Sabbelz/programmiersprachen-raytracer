#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include "ray.hpp"
#include "hitpoint.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Shape{

    public:

    Shape ();
    Shape (glm::vec3 const& color, std::string const& name);

    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual hitpoint intersect(Ray const& r) const = 0;

    virtual std::ostream& print(std::ostream& os) const = 0;

    protected:
    glm::vec3 color_;
    std::string name_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif
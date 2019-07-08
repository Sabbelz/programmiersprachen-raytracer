#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include "ray.hpp"
#include "hitpoint.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "color.hpp"

class Shape{

    public:

    Shape ();
    Shape (Color const& color, std::string const& name);

    virtual ~Shape() {std::cout << "Shape destructor used." <<std::endl;};

    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual hitpoint intersect(Ray const& r) const = 0;

    virtual std::ostream& print(std::ostream& os) const;

    protected:
    Color color_;
    std::string name_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif
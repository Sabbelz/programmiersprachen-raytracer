#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class Shape{

    public:

    Shape ();
    Shape (glm::vec3 color, std::string name);

    virtual float area() const = 0;
    virtual float volume() const = 0;

    virtual std::ostream& print(std::ostream& os) const = 0;

    private:
    glm::vec3 color_;
    std::string name_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif
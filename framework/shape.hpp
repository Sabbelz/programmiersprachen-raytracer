#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <glm/vec3.hpp>
#include <string>

class Shape{

    public:

    Shape ();
    Shape (glm::vec3 color, std::string name);

    virtual float area() const = 0;
    virtual float volume() const = 0;

    private:
    glm::vec3 color_;
    std::string name_;
};


#endif
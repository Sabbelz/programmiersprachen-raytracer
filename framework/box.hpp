#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"


class Box: public Shape{
    public:

    Box();
    Box(glm::vec3 const& max, glm::vec3 const& min);
    Box(glm::vec3 const& max, glm::vec3 const& min, std::string const& name, glm::vec3 const& color);

    float area() const override;
    float volume() const override;

    private:
    glm::vec3 max_;
    glm::vec3 min_;
};

#endif
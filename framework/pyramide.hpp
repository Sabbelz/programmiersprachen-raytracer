#ifndef PYRAMIDE_HPP
#define PYRAMIDE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Pyramide: public Shape{

    public:

    Pyramide();
    Pyramide(glm::vec3 const& pmax, glm::vec3 const& pmin, float height);
    Pyramide(glm::vec3 const& pmax, glm::vec3 const& pmin, float height, std::string const& name, std::shared_ptr<Material> material);

    ~Pyramide();


    private:
    glm::vec3 pmin_;
    glm::vec3 pmax_;
    glm::vec3 tip_;
    float height_;
};

#endif
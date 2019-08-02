#ifndef PYRAMIDE_HPP
#define PYRAMIDE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Pyramide: public Shape{
    public:

    Pyramide();
    Pyramide(glm::vec3 const& pmin,float side, float height);
    Pyramide(glm::vec3 const& pmin,float side, float height, std::string const& name, std::shared_ptr<Material> material);

    ~Pyramide(){/*Destructor */}

    float area() const override;
    float volume() const override;
    hitpoint intersect(Ray const& r) const override;

    std::ostream& print(std::ostream& os) const override;

    private:
    glm::vec3 pmin_;
    glm::vec3 pmax_;
    glm::vec3 tip_;
    float side_;
    float height_;
};

#endif
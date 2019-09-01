#ifndef CONE_HPP
#define CONE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Cone : public Shape {
    public:

    Cone();
    Cone(glm::vec3 const& center, float height, float radius, std::string const& name, std::shared_ptr<Material> material);

    ~Cone(){}

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
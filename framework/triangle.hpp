#ifndef TRINAGLE_HPP
#define TRINAGLE_HPP

#include "shape.hpp"

class Triangle : public Shape {
    public:
    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c,  std::string name, std::shared_ptr<Material> material);
    ~Triangle();
    float area() const override;
    float volume() const override;
    hitpoint intersect(Ray const& r) const override;
    std::ostream& print(std::ostream& os) const override;


    private:
    glm::vec3 a_, b_,c_;

};

#endif
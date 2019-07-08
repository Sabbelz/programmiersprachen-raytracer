#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"



class Box: public Shape{
    public:

    Box();
    Box(glm::vec3 const& max, glm::vec3 const& min);
    Box(glm::vec3 const& max, glm::vec3 const& min, std::string const& name, std::shared_ptr<Material> material);

    ~Box(){std::cout << "Box destructor used"<<std::endl;}

    float area() const override;
    float volume() const override;
    hitpoint intersect(Ray const& r) const override;

    std::ostream& print(std::ostream& os) const override;

    private:
    glm::vec3 max_;
    glm::vec3 min_;
};

#endif
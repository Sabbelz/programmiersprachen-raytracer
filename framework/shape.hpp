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
#include "Material.hpp"
#include <memory>
#include "renderer.hpp"

class Shape{

    public:

    Shape ();
    Shape (std::shared_ptr<Material> material, std::string const& name);

    virtual ~Shape() {/*std::cout << "Shape destructor used." <<std::endl;*/};

    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual hitpoint intersect(Ray const& r) const = 0;

    virtual std::ostream& print(std::ostream& os) const;

    protected:
    std::shared_ptr<Material> material_;
    std::string name_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transfomation_inv_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif
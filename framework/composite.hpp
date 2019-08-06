#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP
#include <glm/vec3.hpp>
#include <string>
#include <vector>
#include "shape.hpp"
#include "box.hpp"
#include "ray.hpp"

class Composite : public Shape{
    public:

    Composite();
    Composite(std::string const& name);
    Composite(std::string const& name, std::vector<std::shared_ptr<Shape>> const& shapes, std::vector<std::shared_ptr<Composite>> const& comp);
    ~Composite();

    void createBoundingBox();

    private:

    std::vector<std::shared_ptr<Shape>> shapes_;
    std::vector<std::shared_ptr<Composite>> composites_;
};

#endif
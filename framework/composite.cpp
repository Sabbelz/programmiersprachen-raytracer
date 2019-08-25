#include "composite.hpp"

Composite::Composite(): Shape{nullptr,"default"}{};

Composite::Composite(std::string const& name): Shape{nullptr,name}{};

Composite::Composite(std::string const& name, std::vector<std::shared_ptr<Shape>> const& shapes, std::vector<std::shared_ptr<Composite>> const& comp):
Shape{nullptr,name},
shapes_{shapes},
composites_{comp}{};

Composite::~Composite(){};

void Composite::createBoundingBox(){};

void Composite::add(std::shared_ptr<Shape> shape){
    shapes_.push_back(shape);
}

void Composite::add(std::shared_ptr<Composite> comp){
    composites_.push_back(comp);
}

std::vector<std::shared_ptr<Shape>> Composite::get_Shape(std::vector<std::shared_ptr<Shape>>& shapes){
    for(std::shared_ptr<Shape> s: shapes_){
        shapes.push_back(s);
    }
    
    for(std::shared_ptr<Composite> c: composites_){
        for(auto c : c->get_Shape(shapes)){
            shapes.push_back(c);
        }
    }
    return shapes;
}

hitpoint Composite::intersect(Ray const& r) const{
    hitpoint temp;
    hitpoint closest;

    for(std::shared_ptr<Shape> s: shapes_){
        temp = s->intersect(r);

        if(temp.hit_ == true && temp.distance_ <= closest.distance_){
            closest = temp;
        }    
    }
return closest;
}

float Composite::area() const {return 0.5f;}

float Composite::volume() const {return 0.5f;};

std::ostream& Composite::print(std::ostream& os) const {return os;}
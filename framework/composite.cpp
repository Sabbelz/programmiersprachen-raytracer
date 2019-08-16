#include "composite.hpp"

Composite::Composite():
name_{"default"},
shapes_{nullptr}, 
composites_{nullptr}{};

Composite::Composite(std::string const& name):
name_{name},
shapes_{nullptr},
composites_{nullptr}{};

Composite::Composite(std::string const& name, std::vector<std::shared_ptr<Shape>> const& shapes, std::vector<std::shared_ptr<Composite>> const& comp):
name_{name},
shapes_{shapes},
composites_{comp}{};

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
        if(temp.distance_ <= closest.distance_){
            closest = temp;
        }    
    }
return closest;
}
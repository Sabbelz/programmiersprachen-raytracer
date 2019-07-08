#ifndef MATERIAL_CPP
#define MATERIAL_CPP
#include "color.hpp"

struct Material{
    std::string name_;

    Color ka;
    Color kd;
    Color ks;

    float m;

    friend std::ostream& operator<<(std::ostream& os, Material const& c){
        os << "(" << c.ka << "," << c.kd << "," << c.ks << "," << c.m << "," << c.name_ <<")\n";
        return os;
    }

};

#endif
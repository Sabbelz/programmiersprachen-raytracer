#ifndef MATERIAL_CPP
#define MATERIAL_CPP
#include "color.hpp"

struct Material{
    std::string name_;

    Color ka;
    Color kd;
    Color ks;

    float m;
    float n; // index of refraction
    float opacity; // opacity index
    float glossy;


    friend std::ostream& operator<<(std::ostream& os, Material const& c){
        os << "({" << c.ka.r << "," << c.ka.g << ","  << c.ka.b << "},"
        << "{" << c.kd.r << "," << c.kd.g << ","  << c.kd.b << "},"
        << "{" << c.ks.r << "," << c.ks.g << ","  << c.ks.b << "}, m: " 
        << c.m << ", n: " << c.n << ", opacity: " << c.opacity << ", glossy: " << c.glossy  << c.name_ <<")\n";
        return os;
    }
};
    

#endif
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
        os << "({" << c.ka.r << "," << c.ka.g << ","  << c.ka.b << "},"
        << "{" << c.kd.r << "," << c.kd.g << ","  << c.kd.b << "},"
        << "{" << c.ks.r << "," << c.ks.g << ","  << c.ks.b << "}," 
        << c.m << "," << c.name_ <<")\n";
        return os;
    }
};
    

#endif
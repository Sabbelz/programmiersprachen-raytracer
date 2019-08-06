#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>
#include "color.hpp"

struct Light{

    Light(std::string name, glm::vec3 pos, Color col, double brightness):
    name_(name), pos_(pos), col_(col), brightness_(brightness){}

    friend std::ostream& operator<<(std::ostream& os, Light const& light){
        os << "Name: " << light.name_
            << "Color: " << light.col_
            << "Brightness" << light.brightness_ << std::endl;
        return os;
    }

    std::string name_;
    Color col_;
    glm::vec3 pos_;
    double brightness_;
};



#endif
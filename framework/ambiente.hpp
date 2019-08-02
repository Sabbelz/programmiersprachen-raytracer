#ifndef AMBIENTE_HPP
#define AMBIENTE_HPP
#include "color.hpp"

struct Ambiente{
    Color col_;

    Ambiente(Color col) : col_(col){};

    friend std::ostream& operator<<(std::ostream& os, Ambiente const& m){
        os << m.col_<< std::endl;
        return os;
    }
};

#endif
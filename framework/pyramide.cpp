#include "pyramide.hpp"

Pyramide::Pyramide():
Shape{},
pmax_{0.0f},
pmin_{0.0f},
tip_{0.0f},
height_{0.0f}{}

Pyramide::Pyramide(glm::vec3 const& pmax, glm::vec3 const& pmin, float height):
Shape{},
height_{height}
{if(pmax.x > pmin.x){
    pmax_= pmax;
    pmin_= pmin;
    }
    else
    {
        pmin_ = pmax;
        pmax_ = pmin;
    }
    tip_ = 0.5f * (pmax_ - pmin_);
    tip_.y += height;
}

Pyramide::Pyramide(glm::vec3 const& pmax, glm::vec3 const& pmin,float height, std::string const& name, std::shared_ptr<Material> material):
Shape{material, name},
height_{height}
{if(pmax.x > pmin.x){
    pmax_= pmax;
    pmin_= pmin;
    }
    else
    {
        pmin_ = pmax;
        pmax_ = pmin;
    }
    tip_ = 0.5f * (pmax_ - pmin_);
    tip_.y += height;
}
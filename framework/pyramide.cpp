#include "pyramide.hpp"
#include <glm/gtx/intersect.hpp>

glm::mat3x4 gaussianElemination3x4(glm::vec3 o, glm::vec3 d , glm::vec3 v, glm::vec3 r1, glm::vec3 r2);

Pyramide::Pyramide():
Shape{},
pmin_{0.0f},
pmax_{0.0f},
apex_{0.0f},
height_{0.0f},
side_{0.0f}{}

Pyramide::Pyramide(glm::vec3 const& pmin,float side, float height):
Shape{},
height_{height},
side_{side},
pmin_{pmin},
pmax_(pmin.x+side,pmin.y,pmin.z+side)
{
    apex_ = 0.5f * (pmax_ - pmin_);
    apex_.y += height;
}

Pyramide::Pyramide(glm::vec3 const& pmin,float side,float height, std::string const& name, std::shared_ptr<Material> material):
Shape{material, name},
height_{height},
side_{side},
pmin_{pmin},
pmax_(pmin.x+side,pmin.y,pmin.z+side)
{
    apex_ = 0.5f * (pmax_ - pmin_);
    apex_.y += height;
}

float Pyramide::volume() const{
    return (side_*side_*height_)/3.0f;
}

float Pyramide::area() const{
    float base = side_*side_;
    float heigth_rectangle = std::sqrt((0.5f*side_)*(0.5f*side_)+height_*height_);
    return base + 2*side_*heigth_rectangle;
}

std::ostream& Pyramide::print(std::ostream& os) const{
    Shape::print(os);
    return os << "Max: " << pmax_.x << pmax_.y << pmax_.z
              << " Min: " << pmin_.x << pmin_.y << pmin_.z
              << " Apex " << apex_.x << apex_.y << apex_.z
              << " Length of side: " << side_
              << " Heigth: " << height_;
}

hitpoint Pyramide::intersect(Ray const& r)const{
    Ray n{r};
    hitpoint hit{};
    bool washit = false;
    float tmin = FLT_MAX;

    /* Base 
    
         p4 x           x p3(max)



    
    p1(min) x           x p2
    
    */
    glm::vec3 p1 = pmin_;
    glm::vec3 p2 = {pmin_.x,pmin_.y,pmax_.z};
    glm::vec3 p3 = pmax_;
    glm::vec3 p4 = {pmax_.x,pmin_.y,pmin_.z};
    
    
    /* CASE 1 - intersection with base */

    float t_base = (p1.y-n.origin.y)/(glm::normalize(n.direction)).y;
    glm::vec3 p_base = n.origin + t_base*(glm::normalize(n.direction));

    if(p_base.x <= p3.x && p_base.x >= p1.x
    && p_base.z <= p3.z && p_base.z >= p1.z){
        washit = true;
        hit.hitpoint_ = p_base;
        tmin = t_base;
    }

    /*CASE 2 - intersection with plane p1,p2,apex */
    glm::vec3 bary;
    auto aux_hit1 = glm::intersectRayTriangle(n.origin, n.direction, apex_, p1, p2,bary);

    if(aux_hit1 == true) {
        glm::mat3x4 d1 = gaussianElemination3x4(n.origin, n.direction, apex_, p1, p2);
        if(d1[2][3] < tmin){
        washit = true;
        hit.hitpoint_ = n.origin + d1[2][3]*n.direction;
        tmin = d1[2][3];
        }
    }


    /*CASE 3 - intersection with plane p1,p4,apex */
    glm::vec3 bary2;
    auto aux_hit2 = glm::intersectRayTriangle(n.origin, n.direction, apex_, p1, p4,bary2);

    if(aux_hit2 == true) {
        glm::mat3x4 d2 = gaussianElemination3x4(n.origin, n.direction, apex_, p1, p4);
        if(d2[2][3] < tmin){
        washit = true;
        hit.hitpoint_ = n.origin + d2[2][3]*n.direction;
        tmin = d2[2][3];
        }
    }


    /*CASE 4 - intersection with plane p2,p3,apex */
    glm::vec3 bary3;
    auto aux_hit3 = glm::intersectRayTriangle(n.origin, n.direction, apex_, p2, p3,bary);

    if(aux_hit3 == true) {
        glm::mat3x4 d3 = gaussianElemination3x4(n.origin, n.direction, apex_, p2, p3);
        if(d3[2][3] < tmin){
        washit = true;
        hit.hitpoint_ = n.origin + d3[2][3]*n.direction;
        tmin = d3[2][3];
        }
    }


    /*CASE 5 - intersection with plane p3,p4,apex */
    glm::vec3 bary4;
    auto aux_hit4 = glm::intersectRayTriangle(n.origin, n.direction, apex_, p3, p4,bary);

    if(aux_hit4 == true) {
        glm::mat3x4 d4 = gaussianElemination3x4(n.origin, n.direction, apex_, p3, p4);
        if(d4[2][3] < tmin){
        washit = true;
        hit.hitpoint_ = n.origin + d4[2][3]*n.direction;
        tmin = d4[2][3];
        }
    }

    return hit;
}

/* 
 * Auxillary function to solve a 3x4 equatation system to find the intersection point of an line and an plane
 * 
 * float s,t,u
 * vec3: o,d,v,r1,r2
 * 
 * ray: o + s*d
 * 
 * plane: v+ t*r1 + u*r2
 * 
 * t*r1 + u*r2 - s*d = o-v
 *
 * r1.x r2.x -d.x|o.x-v.x
 * r1.y r2.y -d.y|o.y-v.y
 * r1.z r2.z -d.z|o.y-v.y
 */
    glm::mat3x4 gaussianElemination3x4(glm::vec3 o, glm::vec3 d , glm::vec3 v, glm::vec3 r1, glm::vec3 r2){
    float lgs[3][4] = {{r1.x,r2.x,-d.x,o.x-v.x},
                        {r1.y,r2.y,-d.y,o.y-v.y},
                        {r1.z,r2.z,-d.z,o.z-v.z}}; 

    /*
     * Divide every row by its first entry, thus the first entry is either 1 or -1
     */
    for(int j = 0; j < 3; ++j) {
        for(int i = 0; i < 4; ++i) {
            if(lgs[j][0]==0){
                break;
            }else {
            lgs[j][i]/=lgs[j][0];
            }
        }
    }        

    /*
     * Substract row 1 from row 2 and 3
     */
    if(lgs[1][0] != 0) {
        if(lgs[1][0] == 1) {
            lgs[1][0]-=lgs[0][0];
            lgs[1][1]-=lgs[0][1];
            lgs[1][2]-=lgs[0][2];
            lgs[1][3]-=lgs[0][3];
        }else
        {
            lgs[1][0]+=lgs[0][0];
            lgs[1][1]+=lgs[0][1];
            lgs[1][2]+=lgs[0][2];
            lgs[1][3]+=lgs[0][3];
        }
    }
    
    if(lgs[2][0] != 0) {
        if(lgs[2][0] == 1) {
            lgs[2][0]-=lgs[0][0];
            lgs[2][1]-=lgs[0][1];
            lgs[2][2]-=lgs[0][2];
            lgs[2][3]-=lgs[0][3];
        }else
        {
            lgs[2][0]+=lgs[0][0];
            lgs[2][1]+=lgs[0][1];
            lgs[2][2]+=lgs[0][2];
            lgs[2][3]+=lgs[0][3];
        }
    }

    /*
     * Divide the second row by its second entry
     */
        for(int i = 0; i < 4; ++i) {
            if(lgs[1][1]==0){
                break;
            }else {
            lgs[1][i]/=lgs[1][1];
            }
        }

    /**
     * Substract row 2 from row 3 and 1
     */
    if(lgs[2][1] != 0) {
        if(lgs[2][1] > 0) {
            // lgs[2][0]-=lgs[1][0];
            lgs[2][1]-=lgs[1][1]*lgs[2][1];
            lgs[2][2]-=lgs[1][2]*lgs[2][1];
            lgs[2][3]-=lgs[1][3]*lgs[2][1];
        }else
        {
            // lgs[2][0]+=lgs[1][0];
            lgs[2][1]+=lgs[1][1]*lgs[2][1];
            lgs[2][2]+=lgs[1][2]*lgs[2][1];
            lgs[2][3]+=lgs[1][3]*lgs[2][1];
        }
    }

    if(lgs[0][1] != 0) {
        if(lgs[0][1] == 1) {
            // lgs[0][0]-=lgs[1][0];
            lgs[0][1]-=lgs[1][1]*lgs[0][1];
            lgs[0][2]-=lgs[1][2]*lgs[0][1];
            lgs[0][3]-=lgs[1][3]*lgs[0][1];
        }else
        {
            // lgs[0][0]+=lgs[1][0];
            lgs[0][1]+=lgs[1][1]*lgs[0][1];
            lgs[0][2]+=lgs[1][2]*lgs[0][1];
            lgs[0][3]+=lgs[1][3]*lgs[0][1];
        }
    }

    /*
     * Divide the thirf row by its third entry
     */
        for(int i = 0; i < 4; ++i) {
            if(lgs[2][2]==0){
                break;
            }else {
            lgs[2][i]/=lgs[2][2];
            }
        }

    /**
     * Substract the third row from the first and second
     */

    if(lgs[0][2] != 0) {
        if(lgs[2][2] > 0) {
            lgs[0][2]-=lgs[2][2]*lgs[0][2];
            lgs[0][3]-=lgs[2][3]*lgs[0][2];
        }else
        {
            lgs[0][2]+=lgs[2][2]*lgs[0][2];
            lgs[0][3]+=lgs[2][3]*lgs[0][2];
        }
    }

    if(lgs[1][2] != 0) {
        if(lgs[2][2] > 0) {
            lgs[1][2]-=lgs[2][2]*lgs[1][2];
            lgs[1][3]-=lgs[2][3]*lgs[1][2];
        }else
        {
            lgs[1][2]+=lgs[2][2]*lgs[1][2];
            lgs[1][3]+=lgs[2][3]*lgs[1][2];
        }
    }

    glm::mat3x4 out{lgs[0][0],lgs[0][1],lgs[0][2],lgs[0][3],
                    lgs[1][0],lgs[1][1],lgs[1][2],lgs[1][3],
                    lgs[2][0],lgs[2][1],lgs[2][2],lgs[2][3]};
    
    return out;
}
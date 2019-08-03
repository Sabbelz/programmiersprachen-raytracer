#include "camera.hpp"

/**
 * The position, direction, xAngle and yAngle are given.
 * To calculate the imageplane we assume, that the width of the imagepalne is 1 (S.33, Einführung-Raytracer).
 * At first we take a closer look at the triangle wich is given by the width, and the xAngle.
 * 
 * The bisectic of the xAngle is our distance to the imageplane and the adjacent side of the triangle. Half the width is the opposide side.
 * Thus, we get the term:
 * 
 * tan(xAngle/2) = 0.5/d
 * 
 * Rearrange this term to calcualte d.
 * 
 * d = 0.5/(tan(xAngle/2))
 * 
 * Now we can take a closer look at the triangle given by the yAngle. The distance is given by the calcualtion above,
 * therefore we have to calulat the hight of the plane.
 * 
 * h = 2d*tan(yAngle/2)
 */

Camera::Camera():
name_{"default"},
pos_{0.0f,0.0f,0.0f},
direction_{0.0f,0.0f,-1.0f},
xAngle_{90.0f},
yAngle_{90.0f},
d_{1.0f}{
    d_ = 0.5/(tan((xAngle_/2)*M_PI / 180.0));
    imageplane.width_ = 1;
    imageplane.height_ = 2*d_*tan((yAngle_/2)*M_PI / 180.0);
};

Camera::Camera(std::string name, glm::vec3 pos, glm::vec3 direction, float xAngle, float yAngle):
name_{name},
pos_{pos},
direction_{glm::normalize(direction)},
xAngle_{xAngle},
yAngle_{yAngle}{
    d_ = 0.5/(tan((xAngle_/2)*M_PI / 180.0));
    imageplane.width_ = 1;
    imageplane.height_ = 2*d_*tan((yAngle/2)*M_PI / 180.0);
}
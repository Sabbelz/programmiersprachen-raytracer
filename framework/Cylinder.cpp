#include "Cylinder.hpp"
#include "renderer.hpp"

Cylinder::Cylinder():
    Shape{},
    center_{0.0f},
    height_{0.0f},
    radius_{0.0f}
{}

Cylinder::Cylinder(glm::vec3 const& center, float height, float radius):
    Shape{},
    center_{center},
    height_{height},
    radius_{radius}
{}

Cylinder::Cylinder(glm::vec3 const& center, float height, float radius, std::string const& name, std::shared_ptr<Material> material):
    Shape{material, name},
    center_{center},
    height_{height},
    radius_{radius}
{}

float Cylinder::area() const{
    float area_o = (2*M_PI*radius_*height_) + (2*M_PI*radius_*radius_ + 2*M_PI*radius_*height_);

    return area_o;

}

float Cylinder::volume() const{
    float volume = M_PI * radius_ * radius_ * height_;
    return volume;
}

std::ostream& Cylinder::print(std::ostream& os) const{
    Shape::print(os);
    return os << " Center: " << center_.x << center_.y << center_.z
              << " Radius: " << radius_ << " Height: " << height_ << "\n";
}
hitpoint Cylinder::intersect(Ray const& r) const{
    Ray transformedRay = transformRay(r, world_transformation_inv_);
    hitpoint hit{};
    float t = 0.0f;
	float a, b, c;
    float t0, t1;

	a = pow(transformedRay.direction.x, 2) + pow(transformedRay.direction.y, 2);
	b = 2 * transformedRay.origin.x*transformedRay.direction.x + 2 * transformedRay.origin.y*transformedRay.direction.y;
	c = pow(transformedRay.origin.x, 2) + pow(transformedRay.origin.y, 2) - 1;

	t0 = (-b + sqrt(pow(b, 2) - 4 * a*c)) / (2 * a);
	t1 = (-b - sqrt(pow(b, 2) - 4 * a*c)) / (2 * a);
    if (pow(b, 2) - 4 * a*c > 0) {
		bool c1 = false;
		bool c2 = false;
		glm::vec3 cut_1, cut_2;

		if (t0 > 0) {
			cut_1 = transformedRay.origin + t1 * transformedRay.direction;
			if (cut_1.z <= 0.0f && cut_1.z >= -1.0f) {
				c1 = true;
			}
		}
		if (t1 > 0) {
			cut_2 = transformedRay.origin + t1 * transformedRay.direction;
			if (cut_2.z <= 0.0f && cut_2.z >= -1.0f) {
				c2 = true;
			}
		}

		if (c1 && c2) {
			if (t1 < t0) {
				hit.hitpoint_ = cut_2;
				hit.distance_ = t1;
				hit.normal_ = glm::normalize(glm::vec3{ hit.hitpoint_.x, hit.hitpoint_.y, 0.0f });
				hit.hit_ = true;
			}
			else {
				hit.hitpoint_ = cut_1;
				hit.distance_ = t0;
				hit.normal_ = glm::normalize(glm::vec3{ hit.hitpoint_.x, hit.hitpoint_.y, 0.0f });
				hit.hit_ = true;
			}
		}
		else if (c1) {
			hit.hitpoint_ = cut_1;
			hit.distance_ = t0;
			hit.normal_= glm::normalize(glm::vec3{ hit.hitpoint_.x, hit.hitpoint_.y, 0.0f });
			hit.hit_ = true;
		}
		else if (c2) {
			hit.hitpoint_ = cut_2;
			hit.distance_ = t1;
			hit.normal_ = glm::normalize(glm::vec3{ hit.hitpoint_.x, hit.hitpoint_.y, 0.0f });
			hit.hit_ = true;
		}

		Plane plane_1{ glm::vec3{ 0,0,-1 }, glm::vec3{ 0,0,-1 } };
		Plane plane_2{ glm::vec3{ 0,0,0 },	glm::vec3{ 0,0,1 } };

		float distance_base_1 = (glm::dot(plane_1.normal_, plane_1.origin_) - glm::dot(transformedRay.origin, plane_1.normal_)) / (glm::dot(transformedRay.direction, plane_1.normal_));
		float distance_base_2 = (glm::dot(plane_2.normal_, plane_2.origin_) - glm::dot(transformedRay.origin, plane_2.normal_)) / (glm::dot(transformedRay.direction, plane_2.normal_));
		float distance_base = distance_base_1;

		if (distance_base_2 > 0 && distance_base_2 < distance_base) {
			distance_base = distance_base_2;
		}
		if (distance_base > 0) {
			glm::vec3  base_cut = transformedRay.origin + distance_base * transformedRay.direction;
			if (glm::length(glm::vec3{ base_cut.x, base_cut.y, 0 }) <= 1) {
				if ((c1 && c2 && distance_base < t0 && distance_base < t1) || (c1 && distance_base < t0) || (c2 && distance_base < t1)) {
					hit.hitpoint_ = base_cut;
					hit.distance_ = distance_base;
					hit.normal_ = glm::normalize(glm::vec3{hit.hitpoint_.x, hit.hitpoint_.y, 0.0f });
					hit.hit_ = true;
				}
			}
		}
		if (hit.hit_) {

			glm::vec4 transformed_cut = world_transformation_ * glm::vec4{ hit.hitpoint_, 1 };
			glm::vec4 transformed_normal = glm::normalize(glm::transpose(world_transformation_inv_) * glm::vec4{ hit.normal_ , 0 });

			hit.hitpoint_ = glm::vec3{ transformed_cut.x, transformed_cut.y, transformed_cut.z };
			hit.normal_ = glm::normalize(glm::vec3{ transformed_normal.x, transformed_normal.y, transformed_normal.z });
			hit.distance_ = glm::length(hit.hitpoint_ - r.origin);
            hit.material_ = material_;
            hit.name_ = name_;
            return hit;
		}
	}
}

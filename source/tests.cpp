#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "../framework/sphere.hpp"
#include "../framework/shape.hpp"
#include "../framework/box.hpp"

TEST_CASE("area/volume", "[arvo]"){
  Box test;
  Box test_1{glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{4.0f,5.0f,2.0f}};
  
  Sphere test_2;
  Sphere test_3{glm::vec3{10.0f, 20.0f, 5.0f}, 1.0f};

  REQUIRE(test_1.area() == 4);
  REQUIRE(test_1.volume() == 8);
  REQUIRE(test.area() == 0);
  REQUIRE(test.volume() == 0);
  REQUIRE(test_2.area() == 0);
  REQUIRE(test_2.volume() == 0);
  REQUIRE(test_3.area() == Approx(12.56637f));
  REQUIRE(test_3.volume() == Approx(4.18879f));
}

TEST_CASE("print", "[pr]"){
  Box test;

  Sphere test_2;

  test.print(std::cout);

  test_2.print(std::cout);

  
}
TEST_CASE ("intersect_ray_sphere", "[intersect]"){

// Ray

glm::vec3 ray_origin{0.0f, 0.0f ,0.0f};

// ray direction has to be normalized !
// you can use :
//v=glm::normalize(some_vector)

glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

// Sphere

glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
float sphere_radius{1.0f};
float distance = 0.0f;
auto result = glm::intersectRaySphere(ray_origin, ray_direction, sphere_center, sphere_radius * sphere_radius ,distance );


// squared radius !!!

REQUIRE (distance == Approx(4.0f));
}

TEST_CASE("intersect", "[its]"){
  Sphere test{glm::vec3{5.0f, 5.0f, 5.0f}, 1.0f};
  Sphere test_1{glm::vec3{10.0f, 10.0f, 10.0f}, 1.0f};

  Ray ray{glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}};
  Ray raymissed{glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{0.0f, -1.0f, 0.0f}};

  hitpoint hit = test.intersect(ray);
  hitpoint missed = test_1.intersect(raymissed);

  REQUIRE(hit.hit_ == true);
  REQUIRE(hit.name_== "default");
  REQUIRE(missed.hit_ == false);
  REQUIRE(missed.name_== "missed");

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "../framework/sphere.hpp"
#include "../framework/shape.hpp"
#include "../framework/box.hpp"
#include "../framework/color.hpp"
#include "../framework/Material.hpp"
#include "../framework/scene.hpp"

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

// TEST_CASE("print", "[pr]"){
//   Box test;

//   Sphere test_2;

//   test.print(std::cout);

//   test_2.print(std::cout);

  
// }
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
  Box box{glm::vec3{10.0f, 10.0f, 10.0f}, glm::vec3{100.0f, 100.0f, 100.0f}};

  Ray ray{glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}};
  Ray raymissed{glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{0.0f, -1.0f, 0.0f}};

  hitpoint hit = test.intersect(ray);
  hitpoint hit_box = box.intersect(ray);
  hitpoint missed_box = box.intersect(raymissed);
  hitpoint missed = test_1.intersect(raymissed);

  REQUIRE(hit.hit_ == true);
  REQUIRE(hit.name_== "default");
  REQUIRE(missed.hit_ == false);
  REQUIRE(missed.name_== "missed");
  REQUIRE(hit_box.hit_ == true);
  REQUIRE(missed_box.hit_ == false);

}

/*TEST_CASE("tastk 5.8", "[task]"){
  Color red{255, 0, 0};
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  Sphere* s1 = new Sphere{position, 1.2f, red, "sphere0"};
  Shape* s2 = new Sphere{position, 1.2f, red, "sphere1"};
  s1->print(std::cout);
  s2->print(std::cout);
  delete s1;
  delete s2;
}*/

TEST_CASE("Sphere")
{
  Material mat{"mat", {0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}, 2.0f};
  auto material = std::make_shared<Material>(mat);
  //auto mat = std::make_shared<Material>("mat", Color{0.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},Color{1.0f,1.0f,1.0f}, 2.0f);
  Sphere s123{{0.0f,0.0f,0.0f}, 3.0f, material , "Hier_könnte_ihre_Werbung_stehen"};
  std::cout << "\n" << s123 <<std::endl;
}

TEST_CASE("Create Materials", "[scene]")
{
  Scene sc{};
  creatematerial(sc);

  auto ptr = sc.search_map("blue");
  std::cout << "In der Map:" <<*ptr << std::endl;
  auto ptr2 = sc.search_set("red");
  std::cout << "In dem Set:" <<*ptr2 <<std::endl;
  auto ptr3 = sc.search_vec("green");
  std::cout << "In dem Vec:" <<*ptr3 <<std::endl;

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
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
int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

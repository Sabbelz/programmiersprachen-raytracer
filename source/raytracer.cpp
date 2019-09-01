#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  unsigned const image_width = 600;
  unsigned const image_height = 600;
  std::string const filename = "Animation";

  std::cout<<"reading sdf  \n";
  Scene scene = read_SDF("/home/sebastian/materials.sdf");
  //Scene scene = read_SDF("/home/luigi/Documents/Sebastian_raytracer/programmiersprachen-raytracer/SDF/materials.sdf");
  
  std::cout<<"reading sdf finished \n";
  Light light1("Licht", {0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}, 0.0);
  Light light2("Licht2", {100.0f,100.0f,50.0f}, {1.0f,1.0f,1.0f}, 1.0);
  Light light3("Licht3", {-6.0f, 30.0f, 10.0f}, {1.0f,1.0f, 1.0f}, 1.0);
  Ambiente amb{{0.93333f,0.93333f,0.0f}};
  Camera cam("Kamera", {0.0f,0.0f,0.0f},{0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f},110);
  auto ptr_light = std::make_shared<Light>(light1);
  auto ptr_light2 = std::make_shared<Light>(light2);
  auto ptr_light3 = std::make_shared<Light>(light3);
  scene.light_.push_back(ptr_light);
  scene.light_.push_back(ptr_light2);
  scene.light_.push_back(ptr_light3);

  Renderer renderer{image_width, image_height, filename, scene};

  //create separate thread to see updates of pixels while rendering
  // std::thread render_thread([&renderer]() {renderer.render();});
  renderer.render();
  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  // render_thread.join();
  return 0;
}

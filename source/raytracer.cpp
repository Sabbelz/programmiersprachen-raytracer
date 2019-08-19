#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  unsigned const image_width = 1366;
  unsigned const image_height = 768;
  std::string const filename = "./checkerboard.ppm";

  Scene scene{};
  Light light1("Licht", {0.0f,0.0f,0.0f}, {0.66f,0.0f,0.66f}, 0.7);
  Ambiente amb{{0.0f,0.0f,1.0f}};
  Camera cam("Kamera", {0.0f,0.0f,0.0f},{0.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f},60);
  Box b1({10.0f,10.0f,100.0f},{15.0f,15.0f,105.0f});


  auto ptr_shared = std::make_shared<Camera>(cam);
  auto ptr_amb = std::make_shared<Ambiente>(amb);
  auto ptr_light = std::make_shared<Light>(light1);
  std::shared_ptr<Shape> ptr_box = std::make_shared<Box>(b1);
  scene.camera_ = ptr_shared;
  scene.light_.push_back(ptr_light);
  scene.root_comp_ = ptr_box;
  scene.ambiente_ = ptr_amb;


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

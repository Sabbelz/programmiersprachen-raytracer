// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "scene.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render();
  void write(Pixel const& p);
  Color calculate_light(hitpoint const& hit, std::shared_ptr<Light> light);
  Color calculate_color(hitpoint const& hit, int counter);
  Color calculate_ambiente(hitpoint const& hit);
  Color calculate_diffuse(hitpoint const& hit);
  Color calculate_specular(hitpoint const& hit);
  Color calculate_reflection(hitpoint const& hit);
  Color tonemapping(Color const& clr);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  Scene scene_;
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

Ray transformRay(Ray const& ray, glm::mat4 m);

#endif // #ifndef BUW_RENDERER_HPP

#pragma once

#include <canvas.h>
#include <matrix.h>
#include <ray.h>
#include <world.h>

class Camera {
 private:
  void set_halves_and_pixel_size();

 public:
  // Constructors
  Camera(size_t hsize, size_t vsize, double fov);

  // Misc
  Ray ray_for_pixel(size_t px, size_t py) const;
  Canvas render(const World& w) const;

  // Member variables
  size_t hsize_;
  size_t vsize_;
  double fov_;
  double pixel_size_;
  double half_height_;
  double half_width_;
  Mat<4> transform_;
};
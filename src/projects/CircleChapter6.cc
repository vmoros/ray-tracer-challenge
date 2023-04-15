#include <canvas.h>
#include <color.h>
#include <intersection.h>
#include <light.h>
#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

static constexpr size_t CANVAS_PIXELS = 1000;
static constexpr double WALL_Z = 10;
static constexpr double WALL_SIZE = 7;
static constexpr double PIXEL_SIZE = WALL_SIZE / CANVAS_PIXELS;
static constexpr double HALF = WALL_SIZE / 2;

int main() {
  std::cout << "Starting Circle Chapter 6 program" << std::endl;
  std::string filename = "CircleCh6.ppm";
  std::ofstream out(filename);

  Tuple ray_origin = Tuple::Point(0, 0, -5);
  Canvas canvas(CANVAS_PIXELS, CANVAS_PIXELS, Color::White());
  Material mat(Color::Blue());
  mat.shininess_ = 20;

  Sphere sphere(Mat<4>::scaler(1, 1, 1), mat);
  PointLight light(Tuple::Point(-10, 10, -10), Color::White());

  for (size_t y = 0; y < CANVAS_PIXELS; ++y) {
    double world_y = HALF - PIXEL_SIZE * y;
    for (size_t x = 0; x < CANVAS_PIXELS; ++x) {
      double world_x = -HALF + PIXEL_SIZE * x;
      Tuple position = Tuple::Point(world_x, world_y, WALL_Z);

      Ray ray(ray_origin, (position - ray_origin).norm());
      if (std::optional<Intersection> maybe_hit =
              Intersection::hit(sphere.intersect(ray));
          maybe_hit.has_value()) {
        Intersection hit = maybe_hit.value();
        Tuple point = ray.position(hit.t_);
        Tuple normal = hit.obj_->normal_at(point);
        Tuple eye = -ray.direction_;
        Color color =
            light.lighting(hit.obj_->material_, &sphere, point, eye, normal);
        canvas.write_pixel(x, y, color);
      }
    }
  }

  out << canvas;
  std::cout << "I just saved the file " << filename << std::endl;
}
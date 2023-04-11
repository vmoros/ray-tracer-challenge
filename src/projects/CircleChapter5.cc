#include <canvas.h>
#include <color.h>
#include <intersection.h>
#include <matrix.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>

#include <fstream>
#include <iostream>
#include <string>

static constexpr size_t CANVAS_PIXELS = 1000;
static constexpr double WALL_Z = 10;
static constexpr double WALL_SIZE = 7;
static constexpr double PIXEL_SIZE = WALL_SIZE / CANVAS_PIXELS;
static constexpr double HALF = WALL_SIZE / 2;
static const Tuple RAY_ORIGIN = Tuple::Point(0, 0, -5);
static const Color COLOR = Color::Red();

int main() {
  std::cout << "Starting Circle Chapter 5 program" << std::endl;
  std::string filename = "CircleCh5.ppm";
  std::ofstream out(filename);

  Canvas canvas(CANVAS_PIXELS, CANVAS_PIXELS);
  Sphere shape;

  for (size_t y = 0; y < CANVAS_PIXELS; ++y) {
    double world_y = HALF - PIXEL_SIZE * y;
    for (size_t x = 0; x < CANVAS_PIXELS; ++x) {
      double world_x = -HALF + PIXEL_SIZE * x;
      Tuple position = Tuple::Point(world_x, world_y, WALL_Z);

      Ray r(RAY_ORIGIN, (position - RAY_ORIGIN).norm());
      if (auto hit = Intersection::hit(shape.intersect(r)); hit.has_value()) {
        canvas.write_pixel(x, y, COLOR);
      }
    }
  }

  out << canvas;
  std::cout << "I just saved the file " << filename << std::endl;
}
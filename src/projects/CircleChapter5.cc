#include <canvas.h>
#include <color.h>
#include <matrix.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>

#include <fstream>
#include <iostream>
#include <string>

static constexpr size_t WIDTH = 500;
static constexpr size_t HEIGHT = 500;
static constexpr size_t VERTICAL_SQUISH = 8;

int main() {
  std::cout << "Starting Circle program" << std::endl;
  std::string filename = "Circle.ppm";
  std::ofstream out(filename);
  Canvas c(WIDTH, HEIGHT);

  // The sphere should have diameter of the whole canvas and be centered at the
  // center of the canvas
  Sphere s(Mat<4>::translator(WIDTH / 2, HEIGHT / 2, 0) *
           Mat<4>::scaler(WIDTH / 2, HEIGHT / VERTICAL_SQUISH, 1));

  for (size_t row = 0; row < WIDTH; ++row) {
    for (size_t col = 0; col < HEIGHT; ++col) {
      Ray r(
          Tuple::Point(static_cast<double>(row), static_cast<double>(col), -1),
          Tuple::Vector(0, 0, 1));
      Color color;
      if (s.intersect(r).empty()) {
        color = Color::Black();
      } else {
        color = Color::Red();
      }
      c.write_pixel(row, col, color);
    }
  }

  out << c;

  std::cout << "I just saved the file " << filename << std::endl;
}
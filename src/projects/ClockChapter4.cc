#include <canvas.h>
#include <color.h>
#include <matrix.h>
#include <tuple.h>

#include <fstream>
#include <iostream>
#include <numbers>

static constexpr size_t WIDTH = 500;
static constexpr size_t HEIGHT = 500;
static constexpr size_t LO = HEIGHT / 30;
static constexpr size_t HOURS = 12;
static constexpr double PI = std::numbers::pi;
// static constexpr size_t HI = 490;

Mat<4> rotateClockwise(Tuple center, double rad) {
  Mat<4> centerToOrigin =
      Mat<4>::translator(-center.x_, -center.y_, -center.z_);
  Mat<4> rotator = Mat<4>::rotator_z(rad);
  Mat<4> originToCenter = centerToOrigin.inverse();

  return originToCenter * rotator * centerToOrigin;
}

int main() {
  std::cout << "Starting Clock program" << std::endl;
  std::string filename = "doesthiswork.ppm";
  std::ofstream out(filename);
  Canvas c(WIDTH, HEIGHT);

  Tuple pencilTip = Tuple::Point(WIDTH / 2, LO, 0);
  Tuple center = Tuple::Point(WIDTH / 2, HEIGHT / 2, 0);

  for (size_t i = 0; i < HOURS; ++i) {
    c.write_pixel(static_cast<size_t>(pencilTip.x_),
                  static_cast<size_t>(pencilTip.y_), Color::White());
    pencilTip = rotateClockwise(center, 2 * PI / HOURS) * pencilTip;
  }

  out << c;

  std::cout << "I just saved the file " << filename << std::endl;
}
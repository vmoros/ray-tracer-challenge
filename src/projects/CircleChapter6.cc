// This is basically the same as the chapter 5 project
// except with Phong lighting/reflection

#include <canvas.h>
#include <color.h>
#include <light.h>
#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

static constexpr size_t DIM = 1000;

int main() {
  std::cout << "Starting Circle Chapter 6 program" << std::endl;
  std::string filename = "CircleCh6.ppm";
  std::ofstream out(filename);
  Canvas c(DIM, DIM);

  // The sphere should have diameter of the whole canvas
  // and be centered at the center of the canvas
  Mat<4> transformation = Mat<4>::translator(DIM / 2, DIM / 2, 0) *
                          Mat<4>::scaler(DIM / 2, DIM / 2, DIM / 2);

  Sphere s(transformation, Material(Color::Pink()));
  Tuple center = Tuple::Point(DIM / 2, DIM / 2, 0);
  PointLight light(center + Tuple::Point(DIM / -3.0, DIM / -3.0, -1.0 * DIM),
                   Color::White());

  for (size_t row = 0; row < DIM; ++row) {
    for (size_t col = 0; col < DIM; ++col) {
      Ray r(Tuple::Point(static_cast<double>(row), static_cast<double>(col),
                         -static_cast<double>(2 * DIM)),
            Tuple::Vector(0, 0, 1).norm());
      Color color;

      std::vector<Intersection> intersections = s.intersect(r);
      if (intersections.empty()) {
        color = Color::White();
      } else {
        Intersection hit = Intersection::hit(intersections).value();
        Tuple point = r.position(hit.t_);
        Tuple normal = hit.obj_.normal_at(point);
        Tuple eye = -r.direction_;

        color = light.lighting(hit.obj_.material_, point, eye, normal);
      }
      c.write_pixel(row, col, color);
    }
  }

  out << c;

  std::cout << "I just saved the file " << filename << std::endl;
}
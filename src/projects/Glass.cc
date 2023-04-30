#include <camera.h>
#include <color.h>
#include <helpers.h>
#include <light.h>
#include <matrix.h>
#include <pattern.h>
#include <plane.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::cout << "Starting Glass Chapter 11 project" << std::endl;

  // Make a plane as the back wall
  Plane back_wall(Mat<4>::translator(0, 0, 20) * Mat<4>::rotator_x(PI / 2));
  //  RingPat ring(Color::Pink(), Color::Green());
  CheckerPat check(Color::White(), Color::Black());
  back_wall.material_.pattern_ = &check;

  //  // Make a glass sphere
  Sphere middle = Sphere::glass_sphere();
  middle.material_.refract_ = 2.2;
  middle.set_transformation(Mat<4>::scaler(1.5, 1.5, 1.5));

  // Make world & camera
  World w({&back_wall, &middle},
          PointLight(Tuple::Point(-10, 10, -10), Color::White()));

  Camera camera(384, 216, PI / 3);
  camera.set_transformation(Mat<4>::view_transform(
      Tuple::Point(0, 0, -4), Tuple::Point(0, 0, 1), Tuple::Vector(0, 1, 0)));

  // Render & save
  auto start = std::chrono::steady_clock::now();
  Canvas canvas = camera.render(w);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Finished rendering the glass world. It took " << elapsed.count()
            << " seconds." << std::endl;

  std::string filename = "Glass.ppm";
  std::ofstream out(filename);
  out << canvas;

  std::cout << "Finished saving the rendering to " << filename << std::endl;
}
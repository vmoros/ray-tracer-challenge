#include <camera.h>
#include <color.h>
#include <cylinder.h>
#include <helpers.h>
#include <light.h>
#include <matrix.h>
#include <plane.h>
#include <tuple.h>
#include <world.h>

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::cout << "Starting Cylinders Chapter 13 project" << std::endl;

  // Make a cylinder
  Cylinder cyl(-1, 1);
  //  cyl.material_ = Material::Glass();

  // Make a plane as the back wall
  Plane back_wall(Mat<4>::translator(0, 0, 20) * Mat<4>::rotator_x(PI / 2));
  CheckerPat check(Color::White(), Color::Black());
  back_wall.material_.pattern_ = &check;

  // Make world & camera
  World w({&cyl, &back_wall},
          PointLight(Tuple::Point(0, 2, 0), Color::White()));

  Camera camera(1000, 1000, PI / 3);
  camera.set_transformation(Mat<4>::view_transform(
      Tuple::Point(0, 4, -4), Tuple::Point(0, 0, 1), Tuple::Vector(0, 1, 0)));

  // Render & save
  auto start = std::chrono::steady_clock::now();
  Canvas canvas = camera.render(w);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Finished rendering the Cylinders world. It took "
            << elapsed.count() << " seconds." << std::endl;

  std::string filename = "Cylinders.ppm";
  std::ofstream out(filename);
  out << canvas;

  std::cout << "Finished saving the rendering to " << filename << std::endl;
}
#include <camera.h>
#include <color.h>
#include <cone.h>
#include <cylinder.h>
#include <helpers.h>
#include <light.h>
#include <matrix.h>
#include <plane.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::cout << "Starting Cylinders Chapter 13 project" << std::endl;

  // Make a cylinder
  //  Cylinder cyl(-1, 1);
  //  cyl.material_ = Material::Glass();

  // Make a cone
  Cone cone(0.0, 2.0, false);
  cone.set_transformation(Mat<4>::scaler(0.4, 1.0, 0.4));
  cone.material_.color_ = Color(145.0 / 256, 132.0 / 256, 109.0 / 256);

  // Make a scoop of ice cream
  Sphere scoop(Mat<4>::translator(0, 2, 0) * Mat<4>::scaler(0.7, 0.7, 0.7));
  //  Sphere scoop(Mat<4>::translator(0.0, 3.0, 0.0) *
  //               Mat<4>::scaler(0.4, 0.4, 0.4));

  // Make a plane as the floor
  Plane floor;
  //  Plane floor(Mat<4>::translator(0, 0, 20) * Mat<4>::rotator_x(PI / 2));
  CheckerPat check(Color::White(), Color::Black());
  floor.material_.pattern_ = &check;

  // Make world & camera
  World w({&cone, &scoop, &floor},
          PointLight(Tuple::Point(-3, 3, -3), Color::White()));

  Camera camera(1000, 1000, PI / 3);
  camera.set_transformation(Mat<4>::view_transform(
      Tuple::Point(0, 3, -5), Tuple::Point(0, 0, 4), Tuple::Vector(0, 1, 0)));

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
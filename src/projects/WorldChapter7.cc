#include <camera.h>
#include <color.h>
#include <helpers.h>
#include <light.h>
#include <matrix.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::cout << "Starting World Chapter 7 project" << std::endl;

  // Make floor
  Sphere floor;
  floor.transformation_ = Mat<4>::scaler(10, 0.01, 10);
  floor.material_.color_ = Color(1, 0.9, 0.9);
  floor.material_.specular_ = 0.0;

  // Make left wall
  Sphere left_wall;
  left_wall.transformation_ =
      Mat<4>::translator(0, 0, 5) * Mat<4>::rotator_y(-PI / 4) *
      Mat<4>::rotator_x(PI / 2) * Mat<4>::scaler(10, 0.1, 10);

  // Make right wall
  Sphere right_wall;
  right_wall.transformation_ =
      Mat<4>::translator(0, 0, 5) * Mat<4>::rotator_y(PI / 4) *
      Mat<4>::rotator_x(PI / 2) * Mat<4>::scaler(10, 0.1, 10);

  // Make large sphere in the middle
  Sphere middle;
  middle.transformation_ = Mat<4>::translator(-0.5, 1, 0.5);
  middle.material_.color_ = Color(0.1, 1, 0.5);
  middle.material_.diffuse_ = 0.7;
  middle.material_.specular_ = 0.3;

  // Make right eye
  Sphere right;
  right.transformation_ =
      Mat<4>::translator(0.0, 1.33, -0.75) * Mat<4>::scaler(0.33, 0.2, 0.33);
  right.material_.color_ = Color(1, 0.8, 0.1);
  right.material_.diffuse_ = 0.7;
  right.material_.specular_ = 0.3;

  // Make left eye
  Sphere left;
  left.transformation_ =
      Mat<4>::translator(-0.8, 1.33, -0.75) * Mat<4>::scaler(0.33, 0.2, 0.33);
  left.material_.color_ = Color(1, 0.8, 0.1);
  left.material_.diffuse_ = 0.7;
  left.material_.specular_ = 0.3;

  // Make mouth
  Sphere mouth;
  mouth.transformation_ =
      Mat<4>::translator(-0.4, 0.75, -0.75) * Mat<4>::scaler(0.5, 0.1, 0.33);
  mouth.material_.color_ = Color::Red();
  mouth.material_.diffuse_ = 0.7;
  mouth.material_.specular_ = 0.3;

  // Make world & camera
  World w({floor, left_wall, right_wall, middle, right, left, mouth},
          PointLight(Tuple::Point(-10, 10, -10), Color(1, 1, 1)));

  Camera camera(1000, 500, PI / 3);
  camera.transform_ = Mat<4>::view_transform(
      Tuple::Point(0, 1.5, -5), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0));

  // Render & save
  Canvas canvas = camera.render(w);

  std::cout << "Finished rendering the world" << std::endl;

  std::string filename = "WorldCh7.ppm";
  std::ofstream out(filename);
  out << canvas;

  std::cout << "Finished saving the rendering to " << filename << std::endl;
}
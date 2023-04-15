#include <camera.h>
#include <color.h>
#include <helpers.h>
#include <light.h>
#include <matrix.h>
#include <plane.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::cout << "Starting Plane Chapter 9 project" << std::endl;

  // Make a plane as the floor
  Plane floor;

  // Make a plane as the back wall
  Plane back_wall;
  back_wall.set_transformation(Mat<4>::rotator_y(PI / 2) *
                               Mat<4>::translator(0, 0, 5) *
                               Mat<4>::rotator_x(PI / 2));

  // Make large sphere in the middle
  Sphere middle;
  middle.set_transformation(Mat<4>::translator(-0.5, 1, 0.5));
  middle.material_.color_ = Color(0.1, 1, 0.5);
  middle.material_.diffuse_ = 0.7;
  middle.material_.specular_ = 0.3;

  // Make right sphere
  Sphere right;
  right.set_transformation(Mat<4>::translator(1.5, 0.5, -0.5) *
                           Mat<4>::scaler(0.5, 0.5, 0.5));
  right.material_.color_ = Color(0.5, 1, 0.1);
  right.material_.diffuse_ = 0.7;
  right.material_.specular_ = 0.3;

  // Make left sphere
  Sphere left;
  left.set_transformation(Mat<4>::translator(-1.5, 0.33, -0.75) *
                          Mat<4>::scaler(0.33, 0.33, 0.33));
  left.material_.color_ = Color(1, 0.8, 0.1);
  left.material_.diffuse_ = 0.7;
  left.material_.specular_ = 0.3;

  // Make world & camera
  World w({&floor, &back_wall, &middle, &right, &left},
          PointLight(Tuple::Point(-10, 10, -10), Color::White()));

  Camera camera(500, 500, PI / 3);
  camera.set_transformation(Mat<4>::view_transform(
      Tuple::Point(0, 1.5, -5), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0)));

  // Render & save
  Canvas canvas = camera.render(w);

  std::cout << "Finished rendering the world" << std::endl;

  std::string filename = "PlaneCh9.ppm";
  std::ofstream out(filename);
  out << canvas;

  std::cout << "Finished saving the rendering to " << filename << std::endl;
}
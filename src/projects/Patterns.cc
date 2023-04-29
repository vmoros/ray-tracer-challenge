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

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::cout << "Starting Patterns Chapter 10 project" << std::endl;

  // Make a plane as the floor
  Plane floor;
  StripePat stripe(Color::White(), Color::Black());
  floor.material_.pattern_ = &stripe;
  //   floor.material_.reflectivity_ = 0.6;

  // // Make a plane as the back wall
  // Plane back_wall(Mat<4>::rotator_y(PI / 2) * Mat<4>::translator(0, 0, 5) *
  //                 Mat<4>::rotator_x(PI / 2));
  // RingPat ring(Color::Pink(), Color::Green());
  // back_wall.material_.pattern_ = &ring;

  // Make large sphere in the middle
  Sphere middle(Mat<4>::translator(-0.5, 1, 0.5));
  middle.material_.color_ = Color(0.1, 1, 0.5);
  middle.material_.diffuse_ = 0.7;
  middle.material_.specular_ = 0.3;
  middle.material_.reflectivity_ = 0.5;
  // CheckerPat checker(Color::Blue(), Color::Red());
  // middle.material_.pattern_ = &checker;

  // Make right sphere
  Sphere right(Mat<4>::translator(1.5, 0.5, -0.5) *
               Mat<4>::scaler(0.5, 0.5, 0.5));
  right.material_.color_ = Color(0.5, 1, 0.1);
  right.material_.diffuse_ = 0.7;
  right.material_.specular_ = 0.3;
  GradientPat gradient(Color::White(), Color::Red());
  right.material_.pattern_ = &gradient;
  right.material_.reflectivity_ = 0.5;

  // Make left sphere
  Sphere left(Mat<4>::translator(-1.5, 0.33, -0.75) *
              Mat<4>::scaler(0.33, 0.33, 0.33));
  left.material_.color_ = Color(1, 0.8, 0.1);
  left.material_.diffuse_ = 0.7;
  left.material_.specular_ = 0.3;
  RingPat queen_ring(Color::Pink(), Color(.1, 0.4, 0.9));
  queen_ring.set_transformation(Mat<4>::scaler(.1, .1, .1));
  left.material_.pattern_ = &queen_ring;

  // Make world & camera
  World w({&floor, &middle, &right, &left},
          PointLight(Tuple::Point(-10, 10, -10), Color::White()));

  Camera camera(6000, 4000, PI / 3);
  camera.set_transformation(Mat<4>::view_transform(
      Tuple::Point(0, 1.5, -7), Tuple::Point(0, 1, 0), Tuple::Vector(0, 1, 0)));

  // Render & save
  auto start = std::chrono::steady_clock::now();
  Canvas canvas = camera.render(w);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Finished rendering the world. It took " << elapsed.count()
            << " seconds." << std::endl;

  std::string filename = "Patterns.ppm";
  std::ofstream out(filename);
  out << canvas;

  std::cout << "Finished saving the rendering to " << filename << std::endl;
}
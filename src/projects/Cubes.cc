#include <camera.h>
#include <color.h>
#include <cube.h>
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
  std::cout << "Starting Cubes Chapter 12 project" << std::endl;

  // Make a plane as the back wall
  Plane back_wall(Mat<4>::translator(0, 0, 20) * Mat<4>::rotator_x(PI / 2));
  //  RingPat ring(Color::Pink(), Color::Green());
  CheckerPat check(Color::White(), Color::Black());
  back_wall.material_.pattern_ = &check;

  // Make a cube as a table-top
  Cube tabletop;
  tabletop.set_transformation(Mat<4>::translator(0, 0, 5) *
                              Mat<4>::scaler(2, 0.03, 1));

  // Make the close-left leg of the table
  Cube closeleft;
  closeleft.set_transformation(Mat<4>::translator(-1.8, -1, 4.2) *
                               Mat<4>::scaler(0.1, 1, 0.1));

  // Make the close-right leg of the table
  Cube closeright;
  closeright.set_transformation(Mat<4>::translator(1.8, -1, 4.2) *
                                Mat<4>::scaler(0.1, 1, 0.1));

  // Make the far-left leg of the table
  Cube farleft;
  farleft.set_transformation(Mat<4>::translator(-1.8, -1, 5.8) *
                             Mat<4>::scaler(0.1, 1, 0.1));

  // Make the far-right leg of the table
  Cube farright;
  farright.set_transformation(Mat<4>::translator(1.8, -1, 5.8) *
                              Mat<4>::scaler(0.1, 1, 0.1));

  // Make ominous glass orb on the table
  Sphere orb(Material::Glass());
  //  Cube orb(Material::Glass());
  //  orb.material_.refract_ = 2.5;
  orb.set_transformation(Mat<4>::translator(0, 1.5, 5) *
                         Mat<4>::scaler(1.5, 1.5, 1.5));

  // Make world & camera
  World w({&back_wall, &tabletop, &closeleft, &closeright, &farleft, &farright,
           &orb},
          PointLight(Tuple::Point(-10, 10, -10), Color::White()));

  Camera camera(6000, 3500, PI / 3);
  camera.set_transformation(Mat<4>::view_transform(
      Tuple::Point(3, 3, -4), Tuple::Point(0, 0, 5), Tuple::Vector(0, 1, 0)));

  // Render & save
  auto start = std::chrono::steady_clock::now();
  Canvas canvas = camera.render(w);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Finished rendering the cube world. It took " << elapsed.count()
            << " seconds." << std::endl;

  std::string filename = "Cubes.ppm";
  std::ofstream out(filename);
  out << canvas;

  std::cout << "Finished saving the rendering to " << filename << std::endl;
}
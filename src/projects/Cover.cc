#include <camera.h>
#include <cube.h>
#include <helpers.h>
#include <plane.h>
#include <sphere.h>
#include <world.h>

#include <chrono>
#include <fstream>
#include <iostream>

int main() {
  std::cout << "Starting the Cover project" << std::endl;

  // Reusable values
  Material whitemat(Color::White());
  whitemat.diffuse_ = 0.7;
  whitemat.ambient_ = 0.1;
  whitemat.specular_ = 0.0;
  whitemat.reflectivity_ = 0.1;

  Material bluemat = whitemat;
  bluemat.color_ = Color(0.537, 0.831, 0.914);

  Material redmat = whitemat;
  redmat.color_ = Color(0.941, 0.322, 0.388);

  Material purplemat = whitemat;
  purplemat.color_ = Color(0.373, 0.404, 0.550);

  auto standardtransf =
      Mat<4>::translator(1, -1, 1) * Mat<4>::scaler(0.5, 0.5, 0.5);
  auto largeobj = standardtransf * Mat<4>::scaler(3.5, 3.5, 3.5);
  auto mediumobj = standardtransf * Mat<4>::scaler(3, 3, 3);
  auto smallobj = standardtransf * Mat<4>::scaler(2, 2, 2);

  // White backdrop
  Plane backdrop(Mat<4>::translator(0, 0, 500) * Mat<4>::rotator_x(PI / 2));
  backdrop.material_.color_ = Color::White();
  backdrop.material_.ambient_ = 1;
  backdrop.material_.diffuse_ = 0;
  backdrop.material_.specular_ = 0;
  //  w.shapes_.push_back(&backdrop);

  // Other shapes
  Sphere sph1(largeobj);
  sph1.material_.color_ = Color(0.373, 0.404, 0.550);
  sph1.material_.diffuse_ = 0.2;
  sph1.material_.ambient_ = 0;
  sph1.material_.specular_ = 1.0;
  sph1.material_.shininess_ = 200;
  sph1.material_.reflectivity_ = 0.7;
  sph1.material_.transparency_ = 0.7;
  sph1.material_.refract_ = 1.5;
  //  w.shapes_.push_back(&sph1);

  Cube c1(Mat<4>::translator(4, 0, 0) * mediumobj, whitemat);
  Cube c2(Mat<4>::translator(8.5, 1.5, -0.5) * largeobj, bluemat);
  Cube c3(Mat<4>::translator(0, 0, 4) * largeobj, redmat);
  Cube c4(Mat<4>::translator(4, 0, 4) * smallobj, whitemat);
  Cube c5(Mat<4>::translator(7.5, 0.5, 4) * mediumobj, purplemat);
  Cube c6(Mat<4>::translator(-0.25, 0.25, 8) * mediumobj, whitemat);
  Cube c7(Mat<4>::translator(4, 1, 7.5) * largeobj, bluemat);
  Cube c8(Mat<4>::translator(10, 2, 7.5) * mediumobj, redmat);
  Cube c9(Mat<4>::translator(8, 2, 12) * smallobj, whitemat);
  Cube c10(Mat<4>::translator(20, 1, 9) * smallobj, whitemat);
  Cube c11(Mat<4>::translator(-0.5, -5, 0.25) * largeobj, bluemat);
  Cube c12(Mat<4>::translator(4, -4, 0) * largeobj, redmat);
  Cube c13(Mat<4>::translator(8.5, -4, 0) * largeobj, whitemat);
  Cube c14(Mat<4>::translator(0, -4, 4) * largeobj, whitemat);
  Cube c15(Mat<4>::translator(-0.5, -4.5, 8) * largeobj, purplemat);
  Cube c16(Mat<4>::translator(0, -8, 4) * largeobj, whitemat);
  Cube c17(Mat<4>::translator(-0.5, -8.5, 8) * largeobj, whitemat);

  // Camera & World
  Camera cam(6000, 4000, 1);
  cam.set_transformation(Mat<4>::view_transform(Tuple::Point(-6, 6, -10),
                                                Tuple::Point(6, -4, 6),
                                                Tuple::Vector(-0.45, 1, 0)));

  World w({&backdrop, &sph1, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10,
           &c11, &c12, &c13, &c14, &c15, &c16, &c17},
          PointLight(Tuple::Point(50, 100, -50), Color(1, 1, 1)));

  // Render & save
  auto start = std::chrono::steady_clock::now();
  Canvas canvas = cam.render(w);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Finished rendering the Cover world. It took " << elapsed.count()
            << " seconds." << std::endl;

  std::string filename = "Cover.ppm";
  std::ofstream out(filename);
  out << canvas;

  std::cout << "Finished saving the rendering to " << filename << std::endl;
}
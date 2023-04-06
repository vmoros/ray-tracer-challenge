#include <matrix.h>
#include <ray.h>
#include <tuple.h>

#include <iostream>

Ray::Ray(Tuple origin, Tuple direction)
    : origin_(origin), direction_(direction) {}

Tuple Ray::position(double t) const { return origin_ + direction_ * t; }

void Ray::print() const {
  std::cout << "Origin: ";
  origin_.print();
  std::cout << "Direction: ";
  direction_.print();
}

Ray Ray::transform(const Mat<4> mat) const {
  return {mat * origin_, mat * direction_};
}
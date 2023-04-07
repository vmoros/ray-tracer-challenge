#include <helpers.h>
#include <tuple.h>

#include <cmath>
#include <iostream>

// Constructors/factories
Tuple::Tuple() : x_(0.0), y_(0.0), z_(0.0), w_(0) {}
Tuple::Tuple(double x, double y, double z, int w)
    : x_(x), y_(y), z_(z), w_(w) {}
Tuple Tuple::Point(double x_, double y_, double z_) { return {x_, y_, z_, 1}; }
Tuple Tuple::Vector(double x_, double y_, double z_) { return {x_, y_, z_, 0}; }
Tuple Tuple::Origin() { return Point(0, 0, 0); }

// Operators
Tuple Tuple::operator+(Tuple other) const {
  return {x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
}
Tuple Tuple::operator-(Tuple other) const { return *this + (-other); }
Tuple Tuple::operator-() const { return {-x_, -y_, -z_, -w_}; }
bool Tuple::operator==(Tuple other) const {
  return dbleq(x_, other.x_) && dbleq(y_, other.y_) && dbleq(z_, other.z_) &&
         (w_ == other.w_);
}
Tuple Tuple::operator*(double scale) const {
  return {x_ * scale, y_ * scale, z_ * scale, static_cast<int>(w_ * scale)};
}
Tuple Tuple::operator/(double scale) const {
  return {x_ / scale, y_ / scale, z_ / scale, static_cast<int>(w_ / scale)};
}

// Misc
bool Tuple::isPoint() const { return w_ == 1; }

bool Tuple::isVector() const { return w_ == 0; }

double Tuple::mag() const {
  return sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
}

Tuple Tuple::norm() const {
  const double myMag = mag();
  return {x_ / myMag, y_ / myMag, z_ / myMag, static_cast<int>(w_ / myMag)};
}

double Tuple::dot(Tuple other) const {
  return x_ * other.x_ + y_ * other.y_ + z_ * other.z_ + w_ * other.w_;
}

Tuple Tuple::cross(Tuple other) const {
  double comp1 = y_ * other.z_ - z_ * other.y_;
  double comp2 = z_ * other.x_ - x_ * other.z_;
  double comp3 = x_ * other.y_ - y_ * other.x_;
  return Vector(comp1, comp2, comp3);
}

void Tuple::print() const {
  std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ", " << w_ << ")"
            << std::endl;
}
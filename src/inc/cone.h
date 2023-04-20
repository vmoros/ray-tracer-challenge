#pragma once

#include <helpers.h>
#include <intersection.h>
#include <shape.h>
#include <tuple.h>

#include <limits>
#include <vector>

class Cone : public Shape {
 public:
  // Constructors
  Cone() : min_(-INFTY), max_(INFTY), closed_(false) {}
  Cone(double min, double max, bool closed = true)
      : min_(min), max_(max), closed_(closed) {}
  Cone(Mat<4> trn, Material mat, double min, double max, bool closed)
      : Shape(trn, mat), min_(min), max_(max), closed_(closed) {}

  // Misc
  [[nodiscard]] std::vector<Intersection> local_intersect(
      Ray ray) const override {
    double a = sqr(ray.direction_.x_) - sqr(ray.direction_.y_) +
               sqr(ray.direction_.z_);
    double b = 2 * ray.origin_.x_ * ray.direction_.x_ -
               2 * ray.origin_.y_ * ray.direction_.y_ +
               2 * ray.origin_.z_ * ray.direction_.z_;
    double c = sqr(ray.origin_.x_) - sqr(ray.origin_.y_) + sqr(ray.origin_.z_);

    std::vector<Intersection> xs;
    intersect_caps(ray, xs);
    if (dbleq(a, 0.0)) {
      if (dbleq(b, 0.0)) {
        return xs;
      } else {
        xs.emplace_back(-c / (2.0 * b), this);
        return xs;
      }
    }

    double disc = sqr(b) - 4 * a * c;

    if (disc < 0) {
      return {};
    }

    double t0 = (-b - sqrt(disc)) / (2 * a);
    double t1 = (-b + sqrt(disc)) / (2 * a);
    if (t0 > t1) {
      std::swap(t0, t1);
    }

    double y0 = ray.origin_.y_ + t0 * ray.direction_.y_;
    if (min_ < y0 && y0 < max_) {
      xs.emplace_back(t0, this);
    }

    double y1 = ray.origin_.y_ + t1 * ray.direction_.y_;
    if (min_ < y1 && y1 < max_) {
      xs.emplace_back(t1, this);
    }

    return xs;
  }

  [[nodiscard]] Tuple local_normal_at(Tuple point) const override {
    double dist = sqr(point.x_) + sqr(point.z_);

    if (dist < 1) {  // end caps
      if (point.y_ >= (max_ - EPS)) {
        return Tuple::Vector(0, 1, 0);
      }
      if (point.y_ <= (min_ + EPS)) {
        return Tuple::Vector(0, -1, 0);
      }
    }

    double y = sqrt(sqr(point.x_) + sqr(point.z_));
    if (point.y_ > 0) {
      y = -y;
    }
    return Tuple::Vector(point.x_, y, point.z_);
  }

  // Member variables - some come from Shape
  double min_;
  double max_;
  bool closed_;

 private:
  void intersect_caps(Ray ray, std::vector<Intersection>& xs) const {
    if (!closed_ || dbleq(ray.direction_.y_, 0.0)) {
      return;
    }

    double t = (min_ - ray.origin_.y_) / ray.direction_.y_;
    if (check_cap(ray, t, abs(min_))) {
      xs.emplace_back(t, this);
    }

    t = (max_ - ray.origin_.y_) / ray.direction_.y_;
    if (check_cap(ray, t, abs(max_))) {
      xs.emplace_back(t, this);
    }
  }

  static bool check_cap(Ray ray, double t, double radius) {
    double x = ray.origin_.x_ + t * ray.direction_.x_;
    double z = ray.origin_.z_ + t * ray.direction_.z_;

    return sqr(x) + sqr(z) <= radius;
  }
};
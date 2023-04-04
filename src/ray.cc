#include <ray.h>
#include <tuple.h>

Ray::Ray(Tuple origin, Tuple direction)
    : origin_(origin), direction_(direction) {}

Tuple Ray::position(double t) const { return origin_ + direction_ * t; }
#include <tuple.h>

#include <cmath>

bool dbleq(double a, double b) {
  const double eps = 0.0000001;
  return abs(a - b) < eps;
}

Tuple::Tuple(double x, double y, double z, int w) : x(x), y(y), z(z), w(w) {}
Tuple Tuple::Point(double x, double y, double z) { return Tuple(x, y, z, 1); }
Tuple Tuple::Vector(double x, double y, double z) { return Tuple(x, y, z, 0); }

Tuple Tuple::operator+(Tuple other) const {
  return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
}
Tuple Tuple::operator-(Tuple other) const {
  return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
}
Tuple Tuple::operator-() const { return Tuple(-x, -y, -z, -w); }

bool Tuple::isPoint() const { return w == 1; }
bool Tuple::isVector() const { return w == 0; }
bool Tuple::operator==(Tuple other) const {
  return dbleq(x, other.x) && dbleq(y, other.y) && dbleq(z, other.z) &&
         (w == other.w);
}

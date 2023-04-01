#include <color.h>
#include <helpers.h>

Color::Color(double r, double g, double b) : Tuple(r, g, b, 0) {}
Color::Color(Tuple t) : Tuple(t) {}

Color Color::operator+(Tuple other) const { return Color(other + *this); }
Color Color::operator-(Tuple other) const { return Color(-other + *this); }
Color Color::operator*(double scale) const {
  return Color(static_cast<Tuple>(*this) * scale);
}
Color Color::operator*(Tuple other) const {
  return Color(r() * other.x_, g() * other.y_, b() * other.z_);
}

double Color::r() const { return x_; }
double Color::g() const { return y_; }
double Color::b() const { return z_; }

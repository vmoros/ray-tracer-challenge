#include <color.h>

#include <algorithm>

static constexpr int MAX_PIXEL = 255;
static constexpr double PINK_G = 0.2;

Color::Color() : Color(0, 0, 0) {}
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

int Color::rclamp() const {
  return std::clamp(static_cast<int>(r() * MAX_PIXEL), 0, MAX_PIXEL);
}
int Color::gclamp() const {
  return std::clamp(static_cast<int>(g() * MAX_PIXEL), 0, MAX_PIXEL);
}
int Color::bclamp() const {
  return std::clamp(static_cast<int>(b() * MAX_PIXEL), 0, MAX_PIXEL);
}

Color Color::Black() { return Color(0.0, 0.0, 0.0); }
Color Color::White() { return Color(1.0, 1.0, 1.0); }
Color Color::Red() { return Color(1.0, 0.0, 0.0); }
Color Color::Green() { return Color(0.0, 1.0, 0.0); }
Color Color::Blue() { return Color(0.0, 0.0, 1.0); }
Color Color::Pink() { return {1.0, PINK_G, 1.0}; }
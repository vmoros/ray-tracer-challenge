#pragma once
#include <tuple.h>

class Color : public Tuple {
 public:
  Color();
  Color(double r, double g, double b);
  explicit Color(Tuple t);

  Color operator+(Tuple other) const;
  Color operator-(Tuple other) const;
  Color operator*(double scale) const;
  Color operator*(Tuple other) const;

  [[nodiscard]] double r() const;
  [[nodiscard]] double g() const;
  [[nodiscard]] double b() const;

  [[nodiscard]] int rclamp() const;
  [[nodiscard]] int gclamp() const;
  [[nodiscard]] int bclamp() const;

  static Color Black();
  static Color White();
  static Color Red();
  static Color Green();
  static Color Blue();
  static Color Pink();
};

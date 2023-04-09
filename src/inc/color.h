#pragma once
#include <tuple.h>

class Color : public Tuple {
 public:
  Color();
  Color(double r, double g, double b);
  Color(Tuple t);

  Color operator+(Tuple other) const;
  Color operator-(Tuple other) const;
  Color operator*(double scale) const;
  Color operator*(Tuple other) const;

  double r() const;
  double g() const;
  double b() const;

  int rclamp() const;
  int gclamp() const;
  int bclamp() const;

  static Color Black();
  static Color White();
  static Color Red();
  static Color Green();
  static Color Blue();
  static Color Pink();
};

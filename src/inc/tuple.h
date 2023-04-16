#pragma once

class Tuple {
 public:
  double x_;
  double y_;
  double z_;
  int w_;

  // Constructors/factories
  Tuple();
  Tuple(double x, double y, double z, int w);
  static Tuple Point(double x, double y, double z);
  static Tuple Vector(double x, double y, double z);
  static Tuple Origin();

  // Operators
  Tuple operator+(Tuple other) const;
  Tuple operator-(Tuple other) const;
  Tuple operator-() const;
  bool operator==(Tuple other) const;
  Tuple operator*(double scale) const;
  Tuple operator/(double scale) const;

  // Misc
  [[nodiscard]] bool isPoint() const;
  [[nodiscard]] bool isVector() const;
  [[nodiscard]] double mag() const;
  [[nodiscard]] Tuple norm() const;
  [[nodiscard]] double dot(Tuple other) const;
  [[nodiscard]] Tuple cross(Tuple other) const;
  void print() const;
  [[nodiscard]] Tuple reflect(Tuple normal) const;
};

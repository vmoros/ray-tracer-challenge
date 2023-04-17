#pragma once

#include <color.h>
#include <matrix.h>
class Shape;
class Tuple;

class Pattern {
 public:
  // Constructors
  explicit Pattern(Mat<4> transformation);
  Pattern() = default;
  virtual ~Pattern() = default;

  // Misc
  Color pattern_at_shape(const Shape* shape, Tuple point) const;
  void set_transformation(Mat<4> transformation) {
    inverse_ = transformation.inverse();
  }

  // Virtual
  [[nodiscard]] virtual Color pattern_at(Tuple point) const = 0;

  // Member variables
  Mat<4> inverse_;
};

class StripePat : public Pattern {
 public:
  // Constructors
  StripePat(Color a, Color b);

  // Misc
  [[nodiscard]] Color pattern_at(Tuple point) const override;

  // Member variables
  Color a_;
  Color b_;
};

class GradientPat : public Pattern {
 public:
  // Constructors
  GradientPat(Color a, Color b) : a_(a), b_(b) {}
  GradientPat() = default;

  // Misc
  [[nodiscard]] Color pattern_at(Tuple point) const override;

  // Member variables
  Color a_;
  Color b_;
};

class RingPat : public Pattern {
 public:
  // Constructors
  RingPat(Color a, Color b) : a_(a), b_(b) {}
  RingPat() = default;

  // Misc
  [[nodiscard]] Color pattern_at(Tuple point) const override;

  // Member variables
  Color a_;
  Color b_;
};

class CheckerPat : public Pattern {
 public:
  // Constructors
  CheckerPat(Color a, Color b) : a_(a), b_(b) {}
  CheckerPat() = default;

  // Misc
  [[nodiscard]] Color pattern_at(Tuple point) const override;

  // Member variables
  Color a_;
  Color b_;
};
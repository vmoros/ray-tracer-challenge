#pragma once

#include <color.h>
#include <matrix.h>
class Shape;  // #include <shape.h>
#include <tuple.h>

class Pattern {
 public:
  // Constructors
  Pattern(Mat<4> transformation);
  Pattern() = default;

  // Misc
  Color pattern_at_shape(const Shape* shape, Tuple point) const;

  // Virtual
  virtual Color pattern_at(Tuple point) const = 0;

  // Member variables
  Mat<4> transformation_;
};

class StripePat : public Pattern {
 public:
  // Constructors
  StripePat(Color a, Color b);

  // Misc
  Color pattern_at(Tuple point) const override;

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
  Color pattern_at(Tuple point) const override;

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
  Color pattern_at(Tuple point) const override;

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
  Color pattern_at(Tuple point) const override;

  // Member variables
  Color a_;
  Color b_;
};
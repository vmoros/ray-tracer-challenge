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

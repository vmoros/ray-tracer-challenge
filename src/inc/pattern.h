#pragma once

#include <color.h>
#include <matrix.h>
class Shape;  // #include <shape.h>
#include <tuple.h>

class StripePat {
 public:
  // Constructors
  StripePat(Color a, Color b);

  // Misc
  Color stripe_at(Tuple point) const;
  Color stripe_at_object(const Shape& object, Tuple point) const;

  // Member variables
  Color a_;
  Color b_;
  Mat<4> transformation_;
};

#pragma once

#include <array>

#include "tuple.h"

template <size_t sz>
class Mat {
  using data = std::array<std::array<double, sz>, sz>;

 private:
  double dot(const Mat<sz>& other, size_t row, size_t col) const;
  std::array<double, sz> col(size_t c) const;

 public:
  data data_;
  Mat(data d);
  Mat();
  bool operator==(const Mat<sz>& other) const;
  Mat<sz> operator*(const Mat<sz>& other) const;
  Tuple operator*(const Tuple tup) const;
  Mat<sz> transp() const;

  static Mat<sz> iden();
};

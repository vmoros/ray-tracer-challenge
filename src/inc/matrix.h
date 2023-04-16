#pragma once

#include <tuple.h>

#include <array>
#include <cstddef>

template <size_t sz>
class Mat {
  using data = std::array<std::array<double, sz>, sz>;

 private:
  double dot(const Mat<sz>& other, size_t row, size_t col) const;
  std::array<double, sz> col(size_t c) const;

 public:
  explicit Mat(data d);
  Mat();
  bool operator==(const Mat<sz>& other) const;
  Mat<sz> operator*(const Mat<sz>& other) const;
  Tuple operator*(Tuple tup) const;
  Mat<sz> transp() const;
  [[nodiscard]] double det() const;
  Mat<sz - 1> submat(size_t row, size_t col) const;
  [[nodiscard]] double minor(size_t row, size_t col) const;
  [[nodiscard]] double cofactor(size_t row, size_t col) const;
  [[nodiscard]] bool isInvertible() const;
  Mat<sz> inverse() const;
  void print() const;

  static Mat<sz> iden();
  static Mat<4> translator(double x, double y, double z);
  static Mat<4> scaler(double x, double y, double z);
  static Mat<4> rotator_x(double rad);
  static Mat<4> rotator_y(double rad);
  static Mat<4> rotator_z(double rad);
  static Mat<4> shearer(double xy, double xz, double yx, double yz, double zx,
                        double zy);
  static Mat<4> view_transform(Tuple from, Tuple to, Tuple up);

  data data_;
};
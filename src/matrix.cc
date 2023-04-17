#include <helpers.h>
#include <matrix.h>
#include <tuple.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <ranges>

template <size_t sz>
Mat<sz>::Mat(data d) : data_(d) {}

template <size_t sz>
Mat<sz>::Mat() : data_({}) {
  for (size_t i = 0; i < sz; ++i) {
    data_[i][i] = 1.0;
  }
}

template <size_t sz>
Mat<sz> Mat<sz>::iden() {
  return Mat<sz>();
}

template <size_t sz>
bool Mat<sz>::operator==(const Mat<sz>& other) const {
  for (size_t row = 0; row < sz; ++row) {
    for (size_t col = 0; col < sz; ++col) {
      if (!dbleq(data_[row][col], other.data_[row][col])) {
        return false;
      }
    }
  }

  return true;
}

template <size_t sz>
double Mat<sz>::dot(const Mat<sz>& other, size_t row, size_t col) const {
  auto inds = std::views::iota(size_t{0}, sz);
  return std::transform_reduce(inds.begin(), inds.end(), 0.0, std::plus{},
                               [row, col, this, &other](size_t i) {
                                 return data_[row][i] * other.data_[i][col];
                               });
}

template <size_t sz>
std::array<double, sz> Mat<sz>::col(size_t c) const {
  auto inds = std::views::iota(size_t{0}, sz);
  std::array<double, sz> ans{};
  std::transform(inds.begin(), inds.end(), ans.begin(),
                 [c, this](size_t i) { return data_[i][c]; });

  return ans;
}

template <size_t sz>
Mat<sz> Mat<sz>::operator*(const Mat<sz>& other) const {
  Mat<sz> ans{};

  for (size_t row = 0; row < sz; ++row) {
    for (size_t col = 0; col < sz; ++col) {
      ans.data_[row][col] = dot(other, row, col);
    }
  }

  return ans;
}

template <>
Tuple Mat<4>::operator*(const Tuple tup) const {
  Tuple ans{};

  ans.x_ = data_[0][0] * tup.x_ + data_[0][1] * tup.y_ + data_[0][2] * tup.z_ +
           data_[0][3] * tup.w_;
  ans.y_ = data_[1][0] * tup.x_ + data_[1][1] * tup.y_ + data_[1][2] * tup.z_ +
           data_[1][3] * tup.w_;
  ans.z_ = data_[2][0] * tup.x_ + data_[2][1] * tup.y_ + data_[2][2] * tup.z_ +
           data_[2][3] * tup.w_;
  ans.w_ = static_cast<int>(data_[3][0] * tup.x_ + data_[3][1] * tup.y_ +
                            data_[3][2] * tup.z_ + data_[3][3] * tup.w_);

  return ans;
}

template <>
double Mat<2>::det() const {
  return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
}

template <size_t sz>
double Mat<sz>::det() const {
  double ans = 0;

  for (size_t i = 0; i < sz; ++i) {
    ans += data_[0][i] * cofactor(0, i);
  }

  return ans;
}

template <size_t sz>
Mat<sz> Mat<sz>::transp() const {
  Mat<sz> ans{};

  for (size_t i = 0; i < sz; ++i) {
    ans.data_[i] = col(i);
  }

  return ans;
}

template <size_t sz>
Mat<4> Mat<sz>::translator(double x, double y, double z) {
  return Mat<4>({{{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}}});
}

template <size_t sz>
Mat<4> Mat<sz>::scaler(double x, double y, double z) {
  return Mat<4>({{{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}}});
}

template <size_t sz>
Mat<4> Mat<sz>::rotator_x(double rad) {
  return Mat<4>({{{1, 0, 0, 0},
                  {0, cos(rad), -sin(rad), 0},
                  {0, sin(rad), cos(rad), 0},
                  {0, 0, 0, 1}}});
}

template <size_t sz>
Mat<4> Mat<sz>::rotator_y(double rad) {
  return Mat<4>({{{cos(rad), 0, sin(rad), 0},
                  {0, 1, 0, 0},
                  {-sin(rad), 0, cos(rad), 0},
                  {0, 0, 0, 1}}});
}

template <size_t sz>
Mat<4> Mat<sz>::rotator_z(double rad) {
  return Mat<4>({{{cos(rad), -sin(rad), 0, 0},
                  {sin(rad), cos(rad), 0, 0},
                  {0, 0, 1, 0},
                  {0, 0, 0, 1}}});
}

template <size_t sz>
Mat<4> Mat<sz>::shearer(double xy, double xz, double yx, double yz, double zx,
                        double zy) {
  return Mat<4>(
      {{{1, xy, xz, 0}, {yx, 1, yz, 0}, {zx, zy, 1, 0}, {0, 0, 0, 1}}});
}

template <size_t sz>
Mat<4> Mat<sz>::view_transform(Tuple from, Tuple to, Tuple up) {
  Tuple forward = (to - from).norm();
  Tuple left = forward.cross(up.norm());
  Tuple true_up = left.cross(forward);
  Mat<4> orientation({{{left.x_, left.y_, left.z_, 0.0},
                       {true_up.x_, true_up.y_, true_up.z_, 0.0},
                       {-forward.x_, -forward.y_, -forward.z_, 0.0},
                       {0.0, 0.0, 0.0, 1.0}}});

  return orientation * Mat<4>::translator(-from.x_, -from.y_, -from.z_);
}

template <size_t sz>
Mat<sz - 1> Mat<sz>::submat(size_t row, size_t col) const {
  Mat<sz - 1> ans{};

  int rowAdj = 0;
  for (size_t r = 0; r < sz; ++r) {
    if (r == row) {
      rowAdj = 1;
      continue;
    }
    int colAdj = 0;
    for (size_t c = 0; c < sz; ++c) {
      if (c == col) {
        colAdj = 1;
        continue;
      }
      ans.data_[r - rowAdj][c - colAdj] = data_[r][c];
    }
  }

  return ans;
}

template <size_t sz>
double Mat<sz>::minor(size_t row, size_t col) const {
  return submat(row, col).det();
}

template <>
double Mat<2>::minor([[maybe_unused]] size_t row,
                     [[maybe_unused]] size_t col) const {
  throw std::runtime_error("Error: tried to take the minor of a 2D matrix");
}

template <size_t sz>
double Mat<sz>::cofactor(size_t row, size_t col) const {
  const auto isEven = [](size_t a) { return (a % 2) == 0; };
  if (isEven(row + col)) {
    return minor(row, col);
  }

  return -minor(row, col);
}

template <size_t sz>
bool Mat<sz>::isInvertible() const {
  return !dbleq(det(), 0.0);
}

template <size_t sz>
Mat<sz> Mat<sz>::inverse() const {
  if (!isInvertible()) {
    throw std::runtime_error("Error: tried to invert a singular matrix");
  }

  Mat<sz> ans{};
  for (size_t row = 0; row < sz; ++row) {
    for (size_t col = 0; col < sz; ++col) {
      double cofac = cofactor(row, col);
      ans.data_[col][row] = cofac / det();
    }
  }

  return ans;
}

template <size_t sz>
void Mat<sz>::print() const {
  for (const auto& row : data_) {
    for (const auto val : row) {
      std::cout << val << ' ';
    }
    std::cout << std::endl;
  }
}

template class Mat<2>;
template class Mat<3>;
template class Mat<4>;
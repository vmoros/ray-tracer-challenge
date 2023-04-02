#include <helpers.h>
#include <matrix.h>

#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <numeric>
#include <ranges>

template <size_t sz>
Mat<sz>::Mat(data d) : data_(d) {}

template <size_t sz>
Mat<sz>::Mat() : data_({}) {}

template <size_t sz>
bool Mat<sz>::operator==(const Mat<sz>& other) const {
  for (size_t row : std::views::iota(0uz, sz)) {
    for (size_t col : std::views::iota(0uz, sz)) {
      if (!dbleq(data_[row][col], other.data_[row][col])) {
        // std::cout << "WRONG!!!! " << data_[row][col] << " is not equal to "
        //           << other.data_[row][col] << std::endl;
        return false;
      }
    }
  }

  return true;
}

template <size_t sz>
double Mat<sz>::dot(const Mat<sz>& other, size_t row, size_t col) const {
  auto inds = std::views::iota(0uz, sz);
  return std::transform_reduce(
      inds.begin(), inds.end(), 0.0, std::plus{},
      [&](size_t i) { return data_[row][i] * other.data_[i][col]; });
}

template <size_t sz>
std::array<double, sz> Mat<sz>::col(size_t c) const {
  auto inds = std::views::iota(0uz, sz);
  std::array<double, sz> ans{};
  std::transform(inds.begin(), inds.end(), ans.begin(),
                 [&](size_t i) { return data_[i][c]; });

  return ans;
}

template <size_t sz>
Mat<sz> Mat<sz>::operator*(const Mat<sz>& other) const {
  Mat<sz> ans{};
  // std::array<size_t, sz> inds{};
  // std::iota(inds.begin(), inds.end(), 0);

  // std::for_each(inds.begin(), inds.end(), [&](size_t row) {
  //   std::for_each(inds.begin(), inds.end(), [&](size_t col) {
  //     ans.data_[row][col] = dot(other, row, col);
  //   });
  // });
  for (size_t row : std::views::iota(0uz, sz)) {
    for (size_t col : std::views::iota(0uz, sz)) {
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

  for (size_t i : std::views::iota(0uz, sz)) {
    ans += data_[0][i] * cofactor(0, i);
  }

  return ans;
}

template <size_t sz>
Mat<sz> Mat<sz>::transp() const {
  Mat<sz> ans{};

  for (size_t i : std::views::iota(0uz, sz)) {
    ans.data_[i] = col(i);
  }

  return ans;
}

template <size_t sz>
Mat<sz> Mat<sz>::iden() {
  Mat<sz> ans{};

  for (size_t i : std::views::iota(0uz, sz)) {
    ans.data_[i][i] = 1.0;
  }

  return ans;
}

template <size_t sz>
Mat<sz - 1> Mat<sz>::submat(size_t row, size_t col) const {
  Mat<sz - 1> ans{};

  int rowAdj = 0;
  for (size_t r : std::views::iota(0uz, sz)) {
    if (r == row) {
      rowAdj = 1;
      continue;
    }
    int colAdj = 0;
    for (size_t c : std::views::iota(0uz, sz)) {
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
  std::terminate();
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
    std::terminate();
  }

  Mat<sz> ans{};
  for (size_t row : std::views::iota(0uz, sz)) {
    for (size_t col : std::views::iota(0uz, sz)) {
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
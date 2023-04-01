#include <matrix.h>

#include <algorithm>
#include <array>
#include <numeric>

template <size_t sz>
Mat<sz>::Mat(data d) : data_(d) {}

template <size_t sz>
Mat<sz>::Mat() : data_({}) {}

template <size_t sz>
bool Mat<sz>::operator==(const Mat<sz>& other) const {
  std::array<size_t, sz> inds{};
  std::iota(inds.begin(), inds.end(), 0);
  return std::all_of(inds.begin(), inds.end(), [&other, this](size_t i) {
    return data_[i] == other.data_[i];
  });
}

template <size_t sz>
double Mat<sz>::dot(const Mat<sz>& other, size_t row, size_t col) const {
  std::array<size_t, sz> inds{};
  std::iota(inds.begin(), inds.end(), 0);
  return std::transform_reduce(
      inds.begin(), inds.end(), 0.0, std::plus{},
      [&](size_t i) { return data_[row][i] * other.data_[i][col]; });
}

template <size_t sz>
Mat<sz> Mat<sz>::operator*(const Mat<sz>& other) const {
  Mat<sz> ans{};
  std::array<size_t, sz> inds{};
  std::iota(inds.begin(), inds.end(), 0);

  std::for_each(inds.begin(), inds.end(), [&](size_t row) {
    std::for_each(inds.begin(), inds.end(), [&](size_t col) {
      ans.data_[row][col] = dot(other, row, col);
    });
  });

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

template class Mat<2>;
template class Mat<3>;
template class Mat<4>;
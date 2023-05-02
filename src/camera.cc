#include <camera.h>
#include <matrix.h>
#include <ray.h>
#include <tuple.h>
#include <world.h>

#include <algorithm>
#include <cmath>
#include <execution>
#include <utility>

void Camera::set_halves_and_pixel_size() {
  double half_view = tan(fov_ / 2);
  double aspect = static_cast<double>(hsize_) / vsize_;

  if (aspect >= 1.0) {
    half_width_ = half_view;
    half_height_ = half_view / aspect;
  } else {
    half_width_ = half_view * aspect;
    half_height_ = half_view;
  }

  pixel_size_ = (half_width_ * 2) / hsize_;
}

Camera::Camera(size_t hsize, size_t vsize, double fov)
    : hsize_(hsize),
      vsize_(vsize),
      fov_(fov),
      pixel_size_(0.0),
      half_height_(0.0),
      half_width_(0.0),
      inverse_(Mat<4>::iden()) {
  set_halves_and_pixel_size();
}

Ray Camera::ray_for_pixel(size_t px, size_t py) const {
  double xoffset = (px + 0.5) * pixel_size_;
  double yoffset = (py + 0.5) * pixel_size_;

  double world_x = half_width_ - xoffset;
  double world_y = half_height_ - yoffset;

  Tuple pixel = inverse_ * Tuple::Point(world_x, world_y, -1.0);
  Tuple origin = inverse_ * Tuple::Origin();
  Tuple direction = (pixel - origin).norm();

  return {origin, direction};
}

Canvas Camera::render(const World& w) const {
  Canvas image(hsize_, vsize_);

  std::vector<std::pair<size_t, size_t>> inds;
  for (size_t y = 0; y < vsize_; ++y) {
    for (size_t x = 0; x < hsize_; ++x) {
      inds.emplace_back(x, y);
    }
  }

  std::for_each(std::execution::par_unseq, inds.cbegin(), inds.cend(),
                [&](const std::pair<size_t, size_t> indpair) {
                  const auto [x, y] = indpair;
                  auto ray = ray_for_pixel(x, y);
                  auto color = w.color_at(ray);
                  image.write_pixel(x, y, color);
                });

  return image;
}

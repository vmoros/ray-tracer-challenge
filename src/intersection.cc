#include <helpers.h>
#include <intersection.h>
#include <shape.h>

#include <optional>
#include <ranges>

Intersection::Intersection(double t, const Shape* obj) : t_(t), obj_(obj) {}

std::optional<Intersection> Intersection::hit(
    const std::vector<Intersection>& intersections) {
  auto filtered = intersections | std::views::filter([](const auto inter) {
                    return inter.t_ >= 0.0;
                  });
  auto ans = std::ranges::min_element(
      filtered, [](const auto a, const auto b) { return a.t_ < b.t_; });

  if (ans == std::ranges::end(filtered)) {
    return std::nullopt;
  }

  return *ans;
}

bool Intersection::operator==(const Intersection other) const {
  return dbleq(t_, other.t_) && (obj_ == other.obj_);
}

Intersection::Comps Intersection::prepare_computations(Ray ray) const {
  Tuple pos = ray.position(t_);

  Intersection::Comps ans = {
      .inside_ = false,
      .t_ = t_,
      .obj_ = obj_,
      .point_ = pos,
      // Deliberately not setting over_point_ because it will be set later
      .eyev_ = -ray.direction_,
      .normalv_ = obj_->normal_at(pos),
  };

  if (ans.normalv_.dot(ans.eyev_) < 0) {
    ans.inside_ = true;
    ans.normalv_ = -ans.normalv_;
  }

  ans.over_point_ = ans.point_ + ans.normalv_ * EPS;
  ans.reflectv_ = ray.direction_.reflect(ans.normalv_);

  return ans;
}
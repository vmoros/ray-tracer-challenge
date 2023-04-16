#include <helpers.h>
#include <intersection.h>
#include <shape.h>

#include <algorithm>
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

// bool Intersection::operator==(const Intersection other) const {
//   return dbleq(t_, other.t_) && (obj_ == other.obj_);
// }

Intersection::Comps Intersection::prepare_computations(
    Ray ray, const std::vector<Intersection>& xs) const {
  Tuple pos = ray.position(t_);

  Intersection::Comps ans = {
      .inside_ = false,
      .t_ = t_,
      .n1_ = 1.0,
      .n2_ = 1.0,
      .obj_ = obj_,
      .point_ = pos,
      .over_point_ = Tuple::Origin(),  // will be changed later, I just need to
                                       // initialize it with something
      .under_point_ = Tuple::Origin(),
      .eyev_ = -ray.direction_,
      .normalv_ = obj_->normal_at(pos),
      .reflectv_ = Tuple::Origin(),  // will be changed later, I just need to
                                     // initialize it with something
  };

  if (ans.normalv_.dot(ans.eyev_) < 0) {
    ans.inside_ = true;
    ans.normalv_ = -ans.normalv_;
  }

  ans.over_point_ = ans.point_ + ans.normalv_ * EPS;
  ans.under_point_ = ans.point_ - ans.normalv_ * EPS;
  ans.reflectv_ = ray.direction_.reflect(ans.normalv_);

  std::vector<const Shape*> containers;
  for (const auto& i : xs) {
    if (i == *this) {
      if (containers.empty()) {
        ans.n1_ = 1.0;
      } else {
        ans.n1_ = containers.back()->material_.refract_;
      }
    }

    if (auto it = std::find(containers.begin(), containers.end(), i.obj_);
        it == containers.end()) {  // not present
      containers.push_back(i.obj_);
    } else {
      containers.erase(it);
    }

    if (i == *this) {
      if (containers.empty()) {
        ans.n2_ = 1.0;
      } else {
        ans.n2_ = containers.back()->material_.refract_;
      }
    }
  }

  return ans;
}

double Intersection::Comps::schlick() const {
  double cosine = eyev_.dot(normalv_);

  if (n1_ > n2_) {
    double n = n1_ / n2_;
    double sin2_t = n * n * (1.0 - (cosine * cosine));
    if (sin2_t > 1.0) {
      return 1.0;
    }

    cosine = sqrt(1.0 - sin2_t);
  }

  double frac = (n1_ - n2_) / (n1_ + n2_);
  double r0 = std::pow(frac, 2);
  return r0 + (1 - r0) * pow(1 - cosine, 5);
}
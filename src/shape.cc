#include <ray.h>
#include <shape.h>

Shape::Shape(Mat<4> transformation, Material material)
    : inverse_(transformation.inverse()), material_(material) {}

std::vector<Intersection> Shape::intersect(Ray r) const {
  Ray local_ray = r.transform(inverse_);

  return local_intersect(local_ray);
}

Tuple Shape::normal_at(Tuple point) const {
  Tuple local_point = inverse_ * point;
  Tuple local_normal = local_normal_at(local_point);
  Tuple world_normal = inverse_.transp() * local_normal;
  world_normal.w_ = 0;

  return world_normal.norm();
}

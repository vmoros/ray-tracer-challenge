#include <ray.h>
#include <shape.h>

std::vector<Intersection> Shape::intersect(Ray r) const {
  Ray local_ray = r.transform(transformation_.inverse());

  return local_intersect(local_ray);
}

Tuple Shape::normal_at(Tuple point) const {
  Tuple local_point = transformation_.inverse() * point;
  Tuple local_normal = local_normal_at(local_point);
  Tuple world_normal = transformation_.inverse().transp() * local_normal;
  world_normal.w_ = 0;

  return world_normal.norm();
}

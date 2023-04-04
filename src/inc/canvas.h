#pragma once

#include <color.h>

#include <ostream>
#include <vector>

class Canvas {
 public:
  std::vector<std::vector<Color>> data_;  // public for tests

  Canvas(size_t w, size_t h);
  size_t width() const;
  size_t height() const;
  void write_pixel(size_t x, size_t y, Color c);
  Color pixel_at(size_t x, size_t y) const;
  friend std::ostream& operator<<(std::ostream& os, const Canvas& c);
};
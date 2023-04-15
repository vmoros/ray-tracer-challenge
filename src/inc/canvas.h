#pragma once

#include <color.h>

#include <cstddef>
#include <ostream>
#include <vector>

class Canvas {
 public:
  // Constructors
  Canvas(size_t w, size_t h, Color bg_color);
  Canvas(size_t w, size_t h);

  // Misc
  size_t width() const;
  size_t height() const;
  void write_pixel(size_t x, size_t y, Color c);
  Color pixel_at(size_t x, size_t y) const;
  friend std::ostream& operator<<(std::ostream& os, const Canvas& c);

  // Member variables
  std::vector<std::vector<Color>> data_;
};
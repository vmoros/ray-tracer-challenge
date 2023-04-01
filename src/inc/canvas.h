#pragma once

#include <vector>

#include "color.h"

class Canvas {
 public:
  std::vector<std::vector<Color>> data_;  // public for tests

  Canvas(size_t w, size_t h);
  size_t width() const;
  size_t height() const;
};
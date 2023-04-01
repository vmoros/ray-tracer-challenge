#include <canvas.h>

Canvas::Canvas(size_t w, size_t h)
    : data_(std::vector<std::vector<Color>>(
          h, std::vector<Color>(w, Color::Black()))) {}
size_t Canvas::width() const { return data_[0].size(); }
size_t Canvas::height() const { return data_.size(); }
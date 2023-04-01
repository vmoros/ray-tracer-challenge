#include <canvas.h>
#include <color.h>

#include <algorithm>

Canvas::Canvas(size_t w, size_t h)
    : data_(std::vector<std::vector<Color>>(
          h, std::vector<Color>(w, Color::Black()))) {}
size_t Canvas::width() const { return data_[0].size(); }
size_t Canvas::height() const { return data_.size(); }

void Canvas::write_pixel(size_t x, size_t y, Color c) { data_[y][x] = c; }
Color Canvas::pixel_at(size_t x, size_t y) const { return data_[y][x]; }

std::ostream& operator<<(std::ostream& ostr, const Canvas& c) {
  ostr << "P3\n";
  ostr << c.width() << " " << c.height() << "\n";
  ostr << "255\n";

  std::for_each(c.data_.begin(), c.data_.end(), [&ostr](const auto& row) {
    std::for_each(row.begin(), row.end(), [&ostr](const Color c) {
      ostr << c.rclamp() << " " << c.gclamp() << " " << c.bclamp() << " ";
    });
    ostr << "\n";
  });

  return ostr;
}

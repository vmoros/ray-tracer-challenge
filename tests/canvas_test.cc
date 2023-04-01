#include <canvas.h>
#include <color.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <string>

TEST(CanvasTest, BlankCanvas_HasRightDimensionsAndIsAllBlack) {
  Canvas c(10, 20);

  EXPECT_EQ(c.width(), 10);
  EXPECT_EQ(c.height(), 20);

  std::for_each(c.data_.begin(), c.data_.end(), [](auto const& row) {
    std::for_each(row.begin(), row.end(),
                  [](Color color) { EXPECT_EQ(color, Color::Black()); });
  });
}

TEST(CanvasTest, PixelWrittenToCanvas_IsStoredCorrectly) {
  Canvas c(10, 20);
  c.write_pixel(2, 3, Color::Red());

  EXPECT_EQ(c.pixel_at(2, 3), Color::Red());
}

TEST(CanvasTest, PpmPixelData_IsCorrect) {
  Canvas c(5, 3);
  c.write_pixel(0, 0, Color(1.5, 0, 0));
  c.write_pixel(2, 1, Color(0, 0.5, 0));
  c.write_pixel(4, 2, Color(-0.5, 0, 1));
  std::string res =
      "P3\n"
      "5 3\n"
      "255\n"
      "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n"
      "0 0 0 0 0 0 0 127 0 0 0 0 0 0 0 \n"
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n";

  std::stringstream s;
  s << c;
  EXPECT_EQ(s.str(), res);
}

TEST(CanvasTest, Ppm_EndsWithNewLine) {
  Canvas c(5, 3);

  std::stringstream s;
  s << c;
  EXPECT_EQ(s.str().back(), '\n');
}
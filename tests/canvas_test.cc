#include <canvas.h>
#include <gtest/gtest.h>

#include <algorithm>

TEST(CanvasTest, BlankCanvas_HasRightDimensionsAndIsAllBlack) {
  Canvas c(10, 20);

  EXPECT_EQ(c.width(), 10);
  EXPECT_EQ(c.height(), 20);

  std::for_each(c.data_.begin(), c.data_.end(), [](auto const& row) {
    std::for_each(row.begin(), row.end(),
                  [](Color color) { EXPECT_EQ(color, Color::Black()); });
  });
}
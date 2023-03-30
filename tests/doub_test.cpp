#include <gtest/gtest.h>
#include <doubler.h>

TEST(DoublerTest, ShouldPass) {
    EXPECT_EQ(doub(3), 6);
}
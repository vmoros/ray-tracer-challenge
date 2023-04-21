#include <group.h>
#include <gtest/gtest.h>
#include <matrix.h>

TEST(GroupTest, DefaultGroup_IsEmpty) {
  Group g;

  EXPECT_EQ(g.inverse_, Mat<4>::iden());
  EXPECT_EQ(g.shapes_.size(), 0);
}

TEST(GroupTest, Shape_CanBeAddedToGroup) { Group g; }
#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>

TEST(basicUnitTest, Metre) {
  EXPECT_EQ(phy::Metre::metre, 1);
  EXPECT_EQ(phy::Metre::kilogram, 0);
  EXPECT_EQ(phy::Metre::second, 0);
  EXPECT_EQ(phy::Metre::ampere, 0);
  EXPECT_EQ(phy::Metre::kelvin, 0);
  EXPECT_EQ(phy::Metre::mole, 0);
  EXPECT_EQ(phy::Metre::candela, 0);
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

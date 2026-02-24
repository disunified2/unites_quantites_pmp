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
TEST(basicUnitTest, Volt) {
  EXPECT_EQ(phy::Volt::metre, 2);
  EXPECT_EQ(phy::Volt::kilogram, 1);
  EXPECT_EQ(phy::Volt::second, -3);
  EXPECT_EQ(phy::Volt::ampere, -1);
  EXPECT_EQ(phy::Metre::kelvin, 0);
  EXPECT_EQ(phy::Metre::mole, 0);
  EXPECT_EQ(phy::Metre::candela, 0);
}

// Testing basic comparison operators
TEST(quantityComparisonTestEquals, trueNoConversion) {
  const phy::Length l1(5);
  const phy::Length l2(5);

  EXPECT_TRUE(l1 == l2);
}
TEST(quantityComparisonTestEquals, falseNoConversion) {
  const phy::Length l1(5);
  const phy::Length l2(6);

  EXPECT_FALSE(l1 == l2);
}
TEST(quantityComparisonTestEquals, trueConversion) {
  const phy::Length l1(5); // 5 meters
  const phy::Qty<phy::Metre, std::centi> l2(500); // 500 centimeters

  EXPECT_TRUE(l1 == l2);
}
TEST(quantityComparisonTestEquals, falseConversion) {
  const phy::Length l1(1);
  const phy::Qty<phy::Metre, std::milli> l2(1001);

  EXPECT_FALSE(l1 == l2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

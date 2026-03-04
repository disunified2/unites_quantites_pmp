#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>

/*
 * Basic tests to make sure initialization is correct
 */

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

/*
 * Basic comparaison operators
 */
// Only need to test for ==, < and > since the others are variants of these

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

TEST(quantityComparisonTestLT, trueNoConversion) {
  const phy::Length l1(5);
  const phy::Length l2(6);

  EXPECT_TRUE(l1 < l2);
}
TEST(quantityComparaisonTestLT, falseNoConversion) {
  const phy::Length l1(5);
  const phy::Length l2(3);

  EXPECT_FALSE(l1 < l2);
}
TEST(quantityComparaisonTestLT, trueConversion) {
  const phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(5500);

  EXPECT_TRUE(l1 < l2);
}
TEST(quantityComparaisonTestLT, falseConversion) {
  const phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(500);

  EXPECT_FALSE(l1 < l2);
}

TEST(quantityComparaisonTestGT, trueNoConversion) {
  const phy::Length l1(5);
  const phy::Length l2(3);

  EXPECT_TRUE(l1 > l2);
}
TEST(quantityComparaisonTestGT, falseNoConversion) {
  const phy::Length l1(5);
  const phy::Length l2(6);

  EXPECT_FALSE(l1 > l2);
}
TEST(quantityComparaisonTestGT, trueConversion) {
  const phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(500);

  EXPECT_TRUE(l1 > l2);
}
TEST(quantityComparaisonTestGT, falseConversion) {
  const phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(6000);

  EXPECT_FALSE(l1 > l2);
}

/*
 * Testing + and - operators
 */

TEST(quantityAddingArithmeticTest, noConversion) {
  const phy::Length l1(5);
  const phy::Length l2(5);
  const auto l3 = l1 + l2;

  EXPECT_EQ(l3.value, 10);
}
TEST(quantityAddingArithmeticTest, conversion) {
  const phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(500);
  const auto l3 = l1 + l2;

  EXPECT_EQ(l3.value, 5500);
}

TEST(quantitySubtractingArithmeticTest, noConversion) {
  const phy::Length l1(5);
  const phy::Length l2(3);
  const auto l3 = l1 - l2;

  EXPECT_EQ(l3.value, 2);
}
TEST(quantitySubtractingArithmeticTest, conversion) {
  const phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(300);
  const auto l3 = l1 - l2;

  EXPECT_EQ(l3.value, 4700);
}

/*
 * Testing += and -= operators
 */

TEST(quantityAddingTest,sameRatioMeters) {
  phy::Length l1(5);
  const phy::Length l2(5);
  l1 += l2;

  EXPECT_EQ(l1.value, 10);
}

TEST(quantityAddingTest,sameRatioMillimeters) {
  phy::Qty<phy::Metre, std::milli> l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(5);
  l1 += l2;

  EXPECT_EQ(l1.value, 10);
}

TEST(quantityAddingTest,sameRatiokilograms) {
  phy::Mass m1(5);
  const phy::Mass m2(5);
  m1 += m2;

  EXPECT_EQ(m1.value, 10);
}

TEST(quantityAddingTest,differentRatioMetersAndMilliEqualValue) {
  phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(5000);
  l1 += l2;

  EXPECT_EQ(l1.value, 10);
}

TEST(quantityAddingTest,differentRatioMilliAndMeters) {
  phy::Qty<phy::Metre, std::milli> l1(5);
  const phy::Length l2(5);
  l1 += l2;

  EXPECT_EQ(l1.value, 5005);
}

TEST(quantityAddingTest,differentRatioMetersAndMilli) {
  phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(5);
  l1 += l2;

  EXPECT_EQ(l1.value, 5);
}

TEST(quantityAddingTest,differentRatioKilosAndGramsEqualValue) {
  phy::Mass m1(5);
  const phy::Qty<phy::Kilogram, std::milli> m2(5000);
  m1 += m2;

  EXPECT_EQ(m1.value, 10);
}

TEST(quantityAddingTest,differentRatioGramsAndKilos) {
  phy::Qty<phy::Kilogram, std::milli> m1(5);
  phy::Mass m2(5);
  m1 += m2;

  EXPECT_EQ(m1.value, 5005);
}

TEST(quantitySubstractingTest,sameRatioMeters) {
  phy::Length l1(5);
  const phy::Length l2(5);
  l1 -= l2;

  EXPECT_EQ(l1.value, 0);
}

TEST(quantitySubstractingTest,sameRatioMillimeters) {
  phy::Qty<phy::Metre, std::milli> l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(5);
  l1 -= l2;

  EXPECT_EQ(l1.value, 0);
}

TEST(quantitySubstractingTest,sameRatioMillimetersNegativeResult) {
  phy::Qty<phy::Metre, std::milli> l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(10);
  l1 -= l2;

  EXPECT_EQ(l1.value, -5);
}

TEST(quantitySubstractingTest,sameRatiokilograms) {
  phy::Mass m1(5);
  const phy::Mass m2(5);
  m1 -= m2;

  EXPECT_EQ(m1.value, 0);
}

TEST(quantitySubstractingTest,differentRatioMetersAndMilliEqualValue) {
  phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(5000);
  l1 -= l2;

  EXPECT_EQ(l1.value, 0);
}

TEST(quantitySubstractingTest,differentRatioMilliAndMeters) {
  phy::Qty<phy::Metre, std::milli> l1(5);
  const phy::Length l2(5);
  l1 -= l2;

  EXPECT_EQ(l1.value, -4995);
}

TEST(quantitySubstractingTest,differentRatioMetersAndMilli) {
  phy::Length l1(5);
  const phy::Qty<phy::Metre, std::milli> l2(5);
  l1 -= l2;

  EXPECT_EQ(l1.value, 5);
}

TEST(quantitySubstractingTest,differentRatioKilosAndGramsEqualValue) {
  phy::Mass m1(5);
  const phy::Qty<phy::Kilogram, std::milli> m2(5000);
  m1 -= m2;

  EXPECT_EQ(m1.value, 0);
}

TEST(quantitySubstractingTest,differentRatioGramsAndKilos) {
  phy::Qty<phy::Kilogram, std::milli> m1(5000);
  phy::Mass m2(5);
  m1 -= m2;

  EXPECT_EQ(m1.value, 0);
}

TEST(quantitySubstractingTest, notEqualZero) {
  phy::Length l1(15);
  const phy::Length l2(5);
  l1 -= l2;

  EXPECT_EQ(l1.value, 10);
}

TEST(quantitySubstractingTest, notEqualZeroNegative) {
  phy::Length l1(5);
  const phy::Length l2(15);
  l1 -= l2;

  EXPECT_EQ(l1.value, -10);
}

using namespace phy::literals;

TEST(litterals, length1) {
  const auto x = 5_metres;

  EXPECT_EQ(x.value, 5);
}

TEST(litterals, length2) {
  const auto x = 1000_metres;

  EXPECT_EQ(x.value, 1000);
}

TEST(litterals, mass1) {
  const auto x = 5_kilograms;

  EXPECT_EQ(x.value, 5);
}

TEST(litterals, mass2) {
  const auto x = 1000_kilograms;

  EXPECT_EQ(x.value, 1000);
}

TEST(litterals, time1) {
  const auto x = 5_seconds;

  EXPECT_EQ(x.value, 5);
}

TEST(litterals, time2) {
  const auto x = 1000_seconds;

  EXPECT_EQ(x.value, 1000);
}

TEST(litterals, celsius1) {
  const auto x = 1_celsius;

  EXPECT_EQ(x.value, 274);
}

TEST(litterals, celsius2) {
  const auto x = 10_celsius;

  EXPECT_EQ(x.value, 283);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

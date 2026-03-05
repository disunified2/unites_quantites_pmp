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

// == Operator
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

TEST(advancedQuantityComparaisonTestEquals, trueNoConversion) {
  const phy::MeterSecond s1(10);
  const phy::MeterSecond s2(10);

  EXPECT_TRUE(s1 == s2);
}
TEST(advancedQuantityComparaisonTestEquals, falseNoConversion) {
  const phy::MeterSecond s1(10);
  const phy::MeterSecond s2(9);

  EXPECT_FALSE(s1 == s2);
}
TEST(advancedQuantityComparaisonTestEquals, trueConversion) {
  const phy::MeterSecond s1(1000);
  const phy::Qty<phy::Speed, std::kilo> s2(1);

  EXPECT_TRUE(s1 == s2);
}
TEST(advancedQuantityComparaisonTestEquals, falseConversion) {
  const phy::MeterSecond s1(1001);
  const phy::Qty<phy::Speed, std::kilo> s2(1);

  EXPECT_FALSE(s1 == s2);
}

// < operator
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

TEST(advancedQuantityComparaisonTestLT, trueNoConversion) {
  const phy::MeterSecond s1(10);
  const phy::MeterSecond s2(11);

  EXPECT_TRUE(s1 < s2);
}
TEST(advancedQuantityComparaisonTestLT, falseNoConversion) {
  const phy::MeterSecond s1(10);
  const phy::MeterSecond s2(9);

  EXPECT_FALSE(s1 < s2);
}
TEST(advancedQuantityComparaisonTestLT, trueConversion) {
  const phy::MeterSecond s1(10);
  const phy::Qty<phy::Speed, std::kilo> s2(1);

  EXPECT_TRUE(s1 < s2);
}
TEST(advancedQuantityComparaisonTestLT, falseConversion) {
  const phy::MeterSecond s1(5000);
  const phy::Qty<phy::Speed, std::kilo> s2(1);

  EXPECT_FALSE(s1 < s2);
}

// > operator
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

TEST(advancedQuantityComparaisonTestGT, trueNoConversion) {
  const phy::MeterSecond s1(10);
  const phy::MeterSecond s2(9);

  EXPECT_TRUE(s1 > s2);
}
TEST(advancedQuantityComparaisonTestGT, falseNoConversion) {
  const phy::MeterSecond s1(10);
  const phy::MeterSecond s2(11);

  EXPECT_FALSE(s1 > s2);
}
TEST(advancedQuantityComparaisonTestGT, trueConversion) {
  const phy::MeterSecond s1(2000);
  const phy::Qty<phy::Speed, std::kilo> s2(1);

  EXPECT_TRUE(s1 > s2);
}
TEST(advancedQuantityComparaisonTestGT, falseConversion) {
  const phy::MeterSecond s1(900);
  const phy::Qty<phy::Speed, std::kilo> s2(1);

  EXPECT_FALSE(s1 > s2);
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
TEST(quantityAddingArithmeticTest, negative) {
  const phy::Length l1(-5);
  const phy::Length l2(5);
  const auto l3 = l1 + l2;

  EXPECT_EQ(l3.value, 0);
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
TEST(quantitySubtractingArithmeticTest, negative) {
  const phy::Length l1(-5);
  const phy::Length l2(5);
  const auto l3 = l1 - l2;

  EXPECT_EQ(l3.value, -10);
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

/*
 * Tests for the weird imperial units
 */

TEST(weirdQuantitiesEqualityTest, footInch) {
  const phy::Foot f(1);
  const phy::Inch i(12);

  EXPECT_TRUE(f == i);
}
TEST(weirdQuantitiesEqualityTest, yardFoot) {
  const phy::Yard y(1);
  const phy::Foot f(3);

  EXPECT_TRUE(f == y);
}
TEST(weirdQuantitiesEqualityTest, mileYard) {
  const phy::Mile m(1);
  const phy::Yard y(1760);

  EXPECT_TRUE(m == y);
}
TEST(weirdQuantitiesEqualityTest, additionEquals) {
  const phy::Inch i1(6);
  const phy::Inch i2(6);
  const phy::Foot f(1);
  const auto i3 = i1 + i2;

  EXPECT_TRUE(f == i3);
}

TEST(weirdQuantitiesLTTest, noConversion) {
  const phy::Inch i1(4);
  const phy::Inch i2(5);

  EXPECT_TRUE(i1 < i2);
}
TEST(weirdQuantitiesLTTest, conversion) {
  const phy::Inch i(13);
  const phy::Foot f(1);

  EXPECT_TRUE(f < i);
}

TEST(weirdQuantitiesGTTest, noConversion) {
  const phy::Inch i1(4);
  const phy::Inch i2(3);

  EXPECT_TRUE(i1 > i2);
}
TEST(weirdQuantitiesGTTest, conversion) {
  const phy::Inch i(13);
  const phy::Foot f(1);

  EXPECT_TRUE(i > f);
}

TEST(weirdQuantitiesAdditionTest, noConversion) {
  const phy::Inch i1(5);
  const phy::Inch i2(5);
  const auto i3 = i1 + i2;

  EXPECT_EQ(i3.value, 10);
}
TEST(weirdQuanitiesAdditionTest, conversion) {
  const phy::Inch i1(5);
  const phy::Foot f(1);
  const auto i2 = i1 + f;

  EXPECT_EQ(i2.value, 17);
}

TEST(weirdQuantitiesSubtractionTest, noConversion) {
  const phy::Inch i1(5);
  const phy::Inch i2(3);
  const auto i3 = i1 - i2;

  EXPECT_EQ(i3.value, 2);
}
TEST(weirdQuantitiesSubtractingTest, conversion) {
  const phy::Foot f(1);
  const phy::Inch i1(1);
  const auto i2 = f - i1;

  EXPECT_EQ(i2.value, 11);
}

/*
 * TODO : Test knots once *operator and /operator is coded
 *        This is due to the fact that knots is a combination and multiplication of multiple quantities
 */


/*
 * Testing usage of literals
 */

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

#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "eigen_position_correction/eigen_functions.h"

TEST(EigenFunctions, CalculateCenterVector_TwoPoints_Positive) {
    std::vector<Eigen::Vector2d> points = {Eigen::Vector2d(1, 2), Eigen::Vector2d(3, 4)};
    Eigen::Vector2d expected_center(2, 3);
    Eigen::Vector2d calculated_center = calculate_center(points);
    EXPECT_TRUE(expected_center.isApprox(calculated_center));
}

TEST(EigenFunctions, CalculateCenterVector_TwoPoints_Negative) {
    std::vector<Eigen::Vector2d> points = {Eigen::Vector2d(-1, -2), Eigen::Vector2d(-3, -4)};
    Eigen::Vector2d expected_center(-2, -3);
    Eigen::Vector2d calculated_center = calculate_center(points);
    EXPECT_TRUE(expected_center.isApprox(calculated_center));
}

TEST(EigenFunctions, CalculateCenterVector_TwoPoints_PositiveNegative) {
    std::vector<Eigen::Vector2d> points = {Eigen::Vector2d(-1, -2), Eigen::Vector2d(3, 4)};
    Eigen::Vector2d expected_center(1, 1);
    Eigen::Vector2d calculated_center = calculate_center(points);
    EXPECT_TRUE(expected_center.isApprox(calculated_center));
}

TEST(EigenFunctions, CalculateCenterVector_ThreePoints) {
    std::vector<Eigen::Vector2d> points = {Eigen::Vector2d(1, 2), Eigen::Vector2d(0, 0), Eigen::Vector2d(3, 4)};
    Eigen::Vector2d expected_center(2, 3);
    Eigen::Vector2d calculated_center = calculate_center(points);
    EXPECT_TRUE(expected_center.isApprox(calculated_center));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

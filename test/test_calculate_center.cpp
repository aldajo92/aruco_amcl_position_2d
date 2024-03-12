#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "position_2d_correction/eigen_functions.h"

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

TEST(EigenFunctionsTest, RotatePoints) {
    // Create a vector of points forming a square around the origin
    Eigen::Vector2d origin = Eigen::Vector2d(0, 0);

    std::vector<Eigen::Vector2d> points = {
        Eigen::Vector2d(-1, -1),
        Eigen::Vector2d(-1, 1),
        Eigen::Vector2d(1, 1),
        Eigen::Vector2d(1, -1)
    };

    // Rotate the square 90 degrees
    auto rotated_points = rotate_points(points, origin, 90);

    // Expected points after rotation
    std::vector<Eigen::Vector2d> expected_points = {
        Eigen::Vector2d(1, -1),
        Eigen::Vector2d(-1, -1),
        Eigen::Vector2d(-1, 1),
        Eigen::Vector2d(1, 1)
    };

    // Check if the rotated points match the expected points
    for (size_t i = 0; i < points.size(); ++i) {
        EXPECT_NEAR(expected_points[i].x(), rotated_points[i].x(), 1e-5);
        EXPECT_NEAR(expected_points[i].y(), rotated_points[i].y(), 1e-5);
    }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

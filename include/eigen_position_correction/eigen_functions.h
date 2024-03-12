#ifndef EIGEN_FUNCTIONS_H
#define EIGEN_FUNCTIONS_H

#include <Eigen/Dense>
#include <vector>

Eigen::Vector2d calculate_center(const Eigen::MatrixXd &points);
Eigen::Vector2d calculate_center(const std::vector<Eigen::Vector2d> &points);
std::vector<Eigen::Vector2d> rotate_points(const std::vector<Eigen::Vector2d> &points_i, double angle_d);
Eigen::Vector2d calculate_translation_error(const std::vector<Eigen::Vector2d> &points_ref, const std::vector<Eigen::Vector2d> &points_i);
std::vector<Eigen::Vector2d> translate_points(const std::vector<Eigen::Vector2d> &points_i, const Eigen::Vector2d &X_delta);
double cost_rotation_ref(const std::vector<Eigen::Vector2d> &points_ref, const std::vector<Eigen::Vector2d> &points_translated, double angle_d);
std::pair<Eigen::Vector2d, double> calculate_correction(const std::vector<Eigen::Vector2d> &points_ref, const std::vector<Eigen::Vector2d> &points_measured, double angle_min, double angle_max, double step);

#endif // EIGEN_FUNCTIONS_H

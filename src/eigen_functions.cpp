#include "eigen_position_correction/eigen_functions.h"

Eigen::Vector2d calculate_center(const Eigen::MatrixXd &points)
{
  int num_points = points.cols();
  // Calculate the center by averaging the first and last points
  Eigen::Vector2d center = (points.col(0) + points.col(num_points - 1)) / 2.0;
  return center;
}

Eigen::Vector2d calculate_center(const std::vector<Eigen::Vector2d> &points)
{
  int num_points = points.size();
  // Calculate the center by averaging the first and last points
  Eigen::Vector2d center = (points[0] + points[num_points - 1]) / 2.0;
  return center;
}

std::vector<Eigen::Vector2d> rotate_points(const std::vector<Eigen::Vector2d> &points_i, double angle_d)
{
  // 1. Calculate center of the points
  Eigen::Vector2d center = calculate_center(points_i);

  // 2. Use center as the origin (translate points)
  std::vector<Eigen::Vector2d> points_c(points_i.size());
  for (int i = 0; i < points_i.size(); ++i)
  {
    points_c[i] = points_i[i] - center;
  }

  // 3. Apply rotation
  double angle_r = M_PI * angle_d / 180.0; // Convert degrees to radians
  Eigen::Matrix2d rotation_matrix;
  rotation_matrix << std::cos(angle_r), -std::sin(angle_r),
      std::sin(angle_r), std::cos(angle_r);
  std::vector<Eigen::Vector2d> points_r(points_c.size());
  for (int i = 0; i < points_c.size(); ++i)
  {
    points_r[i] = rotation_matrix * points_c[i];
  }

  // 4. Translate back to original center point
  std::vector<Eigen::Vector2d> points_new(points_r.size());
  for (int i = 0; i < points_r.size(); ++i)
  {
    points_new[i] = points_r[i] + center;
  }

  return points_new;
}

Eigen::Vector2d calculate_translation_error(const std::vector<Eigen::Vector2d> &points_ref,
                                            const std::vector<Eigen::Vector2d> &points_i)
{
  // 0. Calculate center of reference
  Eigen::Vector2d center_ref = calculate_center(points_ref);

  // 1. Calculate center of the points
  Eigen::Vector2d center = calculate_center(points_i);

  // 2. Calculate error (difference between centers)
  Eigen::Vector2d error = center_ref - center;

  return error;
}

std::vector<Eigen::Vector2d> translate_points(const std::vector<Eigen::Vector2d> &points_i, const Eigen::Vector2d &X_delta)
{
  // Create a new vector to store translated points
  std::vector<Eigen::Vector2d> points_translated(points_i.size());

  // Apply translation to each element
  for (int i = 0; i < points_i.size(); ++i)
  {
    points_translated[i] = points_i[i] + X_delta;
  }

  return points_translated;
}

double cost_rotation_ref(const std::vector<Eigen::Vector2d> &points_ref,
                         const std::vector<Eigen::Vector2d> &points_translated,
                         double angle_d)
{
  // 1. Rotate the translated points
  std::vector<Eigen::Vector2d> points_mod = rotate_points(points_translated, angle_d);

  // 2. Calculate cost based on difference between first and last points
  Eigen::Vector2d error_start = points_ref[0] - points_mod[0];
  double cost_start = error_start.norm(); // Equivalent to norm() in numpy

  Eigen::Vector2d error_end = points_ref[-1] - points_mod[-1];
  double cost_end = error_end.norm();

  // 3. Combine costs (squared error)
  double cost = std::pow(cost_start, 2.0) + std::pow(cost_end, 2.0);

  return cost;
}

std::pair<Eigen::Vector2d, double> calculate_correction(
    const std::vector<Eigen::Vector2d> &points_ref,
    const std::vector<Eigen::Vector2d> &points_measured,
    double angle_min, double angle_max, double step)
{

  // 1. Create array of angles
  std::vector<double> angle_array;
  for (double angle = angle_min; angle <= angle_max; angle += step)
  {
    angle_array.push_back(angle);
  }

  // 2. Calculate translation error
  Eigen::Vector2d X_error = calculate_translation_error(points_ref, points_measured);

  // 3. Translate points based on error
  std::vector<Eigen::Vector2d> points_translated = translate_points(points_measured, X_error);

  // 4. Calculate cost for each angle
  std::vector<double> cost_array(angle_array.size());
  for (int i = 0; i < angle_array.size(); ++i)
  {
    cost_array[i] = cost_rotation_ref(points_ref, points_translated, angle_array[i]);
  }

  // 5. Find angle with minimum cost
  int index = std::min_element(cost_array.begin(), cost_array.end()) - cost_array.begin();
  double angle_selected = angle_array[index];

  // 6. Return error and selected angle
  return std::make_pair(X_error, angle_selected);
}

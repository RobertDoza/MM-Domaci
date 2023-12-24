#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <utility>
#include <vector>
#include <cmath>

double euclidean_distance(const std::pair<double, double> &point1, const std::pair<double, double> &point2);

std::vector<std::pair<double, double>> calculate_locations(const int &num_nodes, const double &min_value, const double &max_value);

std::vector<std::vector<double>> calculate_distances(const std::vector<std::pair<double, double>> &locations);

std::vector<std::vector<double>> calculate_distances(const int &num_nodes, const double &min_value, const double &max_value);

std::vector<std::vector<double>> calculate_populations(const int &num_nodes, const int &num_periods, const double &min_value, const double &max_value);

#endif

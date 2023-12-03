#include <random>

#include "generate.hpp"

double euclidean_distance(const std::pair<double, double> &point1, const std::pair<double, double> &point2) {
	double x1 = point1.first;
	double y1 = point1.second;
	double x2 = point2.first;
	double y2 = point2.second;

	double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
	
	return distance;
}

std::vector<std::pair<double, double>> calculate_locations(const int &num_nodes, const double &min_value, const double &max_value) {
	std::random_device rd;
	
	std::default_random_engine engine(rd());
	
	std::uniform_real_distribution<double> distribution(min_value, max_value);
	
	std::vector<std::pair<double, double>> locations;
	
	for (int i = 0; i < num_nodes; i++) {
		double x = distribution(engine);
		double y = distribution(engine);
		locations.push_back({x, y});
	}
	
	return locations;
}

std::vector<std::vector<double>> calculate_distances(const std::vector<std::pair<double, double>> &locations) {
	int size = locations.size();

	std::vector<std::vector<double>> distances(size, std::vector<double>(size));
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i + 1; j++) {
			double distance = euclidean_distance(locations[i], locations[j]);
			distances[i][j] = distances[j][i] = distance;
		}
	}
	
	return distances;
}

std::vector<std::vector<double>> calculate_distances(const int &num_nodes, const double &min_value, const double &max_value) {
	std::vector<std::pair<double, double>> locations = calculate_locations(num_nodes, min_value, max_value);
	
	std::vector<std::vector<double>> distances = calculate_distances(locations);
	
	return distances;
}

std::vector<std::vector<int>> calculate_populations(const int &num_nodes, const int &num_periods, const double &min_value, const double &max_value) {
	std::random_device rd;
	
	std::default_random_engine engine(rd());
	
	std::uniform_real_distribution<double> distribution(min_value, max_value);
	
	std::vector<std::vector<int>> populations(num_nodes, std::vector<int>(num_periods));
	
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_periods; j++) {
			populations[i][j] = std::round(distribution(engine));
		}
	}
	
	return populations;
}

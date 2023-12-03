#include <iostream>

#include "generate.hpp"

constexpr int num_nodes = 15;
constexpr int num_facilities = 10;

constexpr double dist_min_value = 0.0;
constexpr double dist_max_value = 30.0;

constexpr double pop_min_value = 0.0;
constexpr double pop_max_value = 100.0;

constexpr int num_periods = 5;

int main() {
	std::vector<std::vector<double>> distances = calculate_distances(num_nodes, dist_min_value, dist_max_value);
	
	/*
	for (const std::vector<double> &row : distances) {
		for (const double &value : row) {
			std::cout << value << "\t";
		}
		std::cout << "\n";
	}
	*/
	
	std::vector<std::vector<int>> populations = calculate_populations(num_nodes, num_periods, pop_min_value, pop_max_value);
	
	for (const std::vector<int> &row : populations) {
		for (const int &value : row) {
			std::cout << value << "\t";
		}
		std::cout << "\n";
	}

	return 0;
}

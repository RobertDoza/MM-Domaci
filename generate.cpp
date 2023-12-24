#include <random>
#include <sstream>
#include <iostream>
#include <fstream>

#include "generate.hpp"

constexpr double dist_min_value = 0.0;
constexpr double dist_max_value = 30.0;

constexpr double pop_min_value = 0.0;
constexpr double pop_max_value = 100.0;

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

std::vector<std::vector<double>> calculate_populations(const int &num_nodes, const int &num_periods, const double &min_value, const double &max_value) {
	std::random_device rd;
	
	std::default_random_engine engine(rd());
	
	std::uniform_real_distribution<double> distribution(min_value, max_value);
	
	std::vector<std::vector<double>> populations(num_nodes, std::vector<double>(num_periods));
	
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_periods; j++) {
			populations[i][j] = distribution(engine);
		}
	}
	
	return populations;
}

void generate_test_instance(const unsigned &i, const unsigned &j, const unsigned &t, const unsigned &s, const unsigned &p) {
	ModelInstance instance(i, j, t, s, p);
	
	std::string filename = format_filename(i, j, t, s, p);
	
	std::ofstream file(filename);
	
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file!");
	}
	
	file << instance;
	
	file.close();
}

std::string format_filename(const unsigned &i, const unsigned &j, const unsigned &t, const unsigned &s, const unsigned &p) {
	std::stringstream buffer;
	
	buffer << i;
	buffer << "_";
	buffer << j;
	buffer << "_";
	buffer << t;
	buffer << "_";
	buffer << s;
	buffer << "_";
	buffer << p;
	buffer << ".txt";
	
	return buffer.str();
}

ModelInstance::ModelInstance(const unsigned &i, const unsigned &j, const unsigned &t, const unsigned &s, const unsigned &p)
	:_num_nodes(i), _num_facilities(j), _num_periods(t), _coverage_radius(s), _total_facilities(p)
{
	_population_matrix = calculate_populations(_num_nodes, _num_periods, pop_min_value, pop_max_value);
	_distance_matrix = calculate_distances(_num_nodes, dist_min_value, dist_max_value);
}

std::ostream& operator << (std::ostream &o, const ModelInstance &i) {
	o << i.to_string();
	
	return o;
}

std::string ModelInstance::to_string() const {
	std::stringstream buffer;
	
	buffer << _num_nodes << " ";
	buffer << _num_facilities << " ";
	buffer << _num_periods << " ";
	buffer << _coverage_radius << " ";
	buffer << _total_facilities << "\n";
	
	for (const std::vector<double> &row : _population_matrix) {
		for (const double &value : row) {
			buffer << value << "\t";
		}
		buffer << "\n";
	}
	
	for (const std::vector<double> &row : _distance_matrix) {
		for (const double &value : row) {
			buffer << value << "\t";
		}
		buffer << "\n";
	}
	
	return buffer.str();
}

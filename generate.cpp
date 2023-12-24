#include <random>
#include <sstream>
#include <iostream>
#include <fstream>

#include "generate.hpp"

double euclidean_distance(const std::pair<double, double> &point1, const std::pair<double, double> &point2) {
	double x1 = point1.first;
	double y1 = point1.second;
	double x2 = point2.first;
	double y2 = point2.second;

	double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
	
	return distance;
}

void generate_test_instance(const ModelParameters &mp, const GenerationParameters &gp) {
	ModelInstance instance(mp, gp);
	
	std::string filename = format_filename(mp);
	
	std::ofstream file(filename);
	
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file!");
	}
	
	file << instance;
	
	file.close();
}

std::string format_filename(const ModelParameters &parameters) {
	std::stringstream buffer;
	
	buffer << parameters.i;
	buffer << "_";
	buffer << parameters.j;
	buffer << "_";
	buffer << parameters.t;
	buffer << "_";
	buffer << parameters.s;
	buffer << "_";
	buffer << parameters.p;
	buffer << ".txt";
	
	return buffer.str();
}

ModelInstance::ModelInstance(const ModelParameters &p, const GenerationParameters &g)
	:_num_nodes(p.i), _num_facilities(p.j), _num_periods(p.t), _coverage_radius(p.s), _total_facilities(p.p),
	_population_matrix(p.i, std::vector<double>(p.t)), _distance_matrix(p.i, std::vector<double>(p.i))
{
	initialize_populations(g.pop_min_value, g.pop_max_value);
	initialize_distances(g.dist_min_value, g.dist_max_value);
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

void ModelInstance::initialize_populations(const double &min_value, const double &max_value) {
	std::random_device rd;
	
	std::default_random_engine engine(rd());
	
	std::uniform_real_distribution<double> distribution(min_value, max_value);
	
	for (unsigned i = 0; i < _num_nodes; i++) {
		for (unsigned j = 0; j < _num_periods; j++) {
			_population_matrix[i][j] = distribution(engine);
		}
	}
}

void ModelInstance::initialize_distances(const double &min_value, const double &max_value) {
	std::vector<std::pair<double, double>> locations = calculate_locations(_num_nodes, min_value, max_value);
	
	int size = locations.size();
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i + 1; j++) {
			double distance = euclidean_distance(locations[i], locations[j]);
			_distance_matrix[i][j] = _distance_matrix[j][i] = distance;
		}
	}
}

std::vector<std::pair<double, double>> ModelInstance::calculate_locations(const int &num_nodes, const double &min_value, const double &max_value) {
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

#include <sstream>

#include "model_instance.hpp"
#include "generate.hpp"

constexpr double dist_min_value = 0.0;
constexpr double dist_max_value = 30.0;

constexpr double pop_min_value = 0.0;
constexpr double pop_max_value = 100.0;

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

#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <utility>
#include <vector>
#include <cmath>
#include <vector>
#include <ostream>

double euclidean_distance(const std::pair<double, double> &point1, const std::pair<double, double> &point2);

std::vector<std::pair<double, double>> calculate_locations(const int &num_nodes, const double &min_value, const double &max_value);

std::vector<std::vector<double>> calculate_distances(const std::vector<std::pair<double, double>> &locations);

std::vector<std::vector<double>> calculate_distances(const int &num_nodes, const double &min_value, const double &max_value);

std::vector<std::vector<double>> calculate_populations(const int &num_nodes, const int &num_periods, const double &min_value, const double &max_value);

void generate_test_instance(const unsigned &i, const unsigned &j, const unsigned &t, const unsigned &s, const unsigned &p);

std::string format_filename(const unsigned &i, const unsigned &j, const unsigned &t, const unsigned &s, const unsigned &p);

class ModelInstance {
	public:
		ModelInstance(const unsigned&, const unsigned&, const unsigned&, const unsigned&, const unsigned&);
		
		friend std::ostream& operator << (std::ostream&, const ModelInstance&);
	private:
		unsigned _num_nodes;
		unsigned _num_facilities;
		unsigned _num_periods;
		unsigned _coverage_radius;
		unsigned _total_facilities;
		std::vector<std::vector<double>> _population_matrix;
		std::vector<std::vector<double>> _distance_matrix;
		
		std::string to_string() const;
};

#endif

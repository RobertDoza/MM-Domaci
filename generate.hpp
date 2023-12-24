#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <utility>
#include <vector>
#include <cmath>
#include <vector>
#include <ostream>

struct ModelParameters {
	unsigned i;
	unsigned j;
	unsigned t;
	unsigned s;
	unsigned p;
};

struct GenerationParameters {
	double dist_min_value;
	double dist_max_value;
	
	double pop_min_value;
	double pop_max_value;
};

double euclidean_distance(const std::pair<double, double> &point1, const std::pair<double, double> &point2);

void generate_test_instance(const ModelParameters&, const GenerationParameters&);

std::string format_filename(const ModelParameters&);

class ModelInstance {
	public:
		ModelInstance(const ModelParameters&, const GenerationParameters&);
		
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
		void initialize_populations(const double &min_value, const double &max_value);
		void initialize_distances(const double &min_value, const double &max_value);
		static std::vector<std::pair<double, double>> calculate_locations(const int &num_nodes, const double &min_value, const double &max_value);
};

#endif

#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <utility>
#include <vector>
#include <cmath>
#include <ostream>

struct ModelParameters {
	unsigned i;
	unsigned j;
	unsigned t;
	double s;
	unsigned p;
};

struct GenerationParameters {
	double dist_min_value;
	double dist_max_value;
	
	double pop_min_value;
	double pop_max_value;
};

class ModelInstance {
	public:
		ModelInstance(const ModelParameters&, const GenerationParameters&);
		
		friend std::ostream& operator << (std::ostream&, const ModelInstance&);
	private:
		unsigned _num_nodes;
		unsigned _num_facilities;
		unsigned _num_periods;
		double _coverage_radius;
		unsigned _total_facilities;
		std::vector<std::vector<double>> _population_matrix;
		std::vector<std::vector<double>> _distance_matrix;
		
		std::string to_string() const;
		void initialize_populations(const double&, const double&);
		void initialize_distances(const double&, const double&);
};

void generate_test_instances(const GenerationParameters&);

std::vector<ModelParameters> read_parameters_from_file(const std::string &filename);

void generate_test_instance(const ModelParameters&, const GenerationParameters&);

std::string format_filename(const ModelParameters&);

double euclidean_distance(const std::pair<double, double>&, const std::pair<double, double>&);

std::vector<std::pair<double, double>> calculate_locations(const int&, const double&, const double&);

#endif

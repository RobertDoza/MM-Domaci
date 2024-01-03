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

constexpr GenerationParameters default_generation_parameters = {0.0, 30.0, 0.0, 100.0};
constexpr std::string_view default_output_directory = "Output";

class ModelInstance {
	public:
		ModelInstance(const ModelParameters&, const GenerationParameters&);
		
		std::string to_cplex_string() const;
		ModelParameters get_model_parameters() const;
		
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

void generate_test_instances(const std::string&, const GenerationParameters& = default_generation_parameters);

std::vector<ModelParameters> read_parameters_from_file(const std::string&);

void generate_cpp_test_instance(const ModelInstance&, const std::string& = std::string(default_output_directory));

void generate_cplex_test_instance(const ModelInstance&, const std::string& = std::string(default_output_directory));

std::string format_filename(const ModelParameters&);

std::string format_cpp_instance_filename(const ModelParameters&);

std::string format_cplex_instance_filename(const ModelParameters&);

double euclidean_distance(const std::pair<double, double>&, const std::pair<double, double>&);

std::vector<std::pair<double, double>> calculate_locations(const int&, const double&, const double&);

#endif

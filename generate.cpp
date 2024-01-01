#include <random>
#include <sstream>
#include <iostream>
#include <fstream>

#include "generate.hpp"

void generate_test_instances(const GenerationParameters &generation_parameters) {
	std::vector<ModelParameters> parameters = read_parameters_from_file("Input/parameters.txt");
	
	for (const ModelParameters &model_parameters : parameters) {
		std::cout
			<< "\rgenerating: "
			<< model_parameters.i << "\t"
			<< model_parameters.j << "\t"
			<< model_parameters.t << "\t"
			<< model_parameters.s << "\t"
			<< model_parameters.p << "\n";
		generate_test_instance(model_parameters, generation_parameters);
	}
}

std::vector<ModelParameters> read_parameters_from_file(const std::string &filename) {
	std::ifstream file(filename);
	
	if (!file.is_open()) {
		throw std::runtime_error("Error reading from file!");
	}
	
	std::vector<ModelParameters> parameters = {};
	
	ModelParameters mp;
	while (file >> mp.i >> mp.j >> mp.t >> mp.s >> mp.p) {		
		parameters.push_back(mp);
	}
	
	file.close();
	
	return parameters;
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

void generate_cplex_test_instance(const ModelParameters &mp, const GenerationParameters &gp) {
	ModelInstance instance(mp, gp);
	
	std::string filename = format_filename(mp);
	
	std::ofstream file(filename);
	
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file!");
	}
	
	file << instance.to_cplex_string();
	
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

std::string ModelInstance::to_cplex_string() const {
	std::stringstream buffer;
	
	buffer << "I = " << _num_nodes << ";\n";
	buffer << "J = " << _num_facilities << ";\n";
	buffer << "T = " << _num_periods << ";\n";
	buffer << "S = " << _coverage_radius << ";\n";
	buffer << "p = " << _total_facilities << ";\n";
	
	bool add_comma, add_inner_comma;
	
	add_comma = false;
	buffer << "pop = [";
	for (const std::vector<double> &row : _population_matrix) {
		if (add_comma) {
			buffer << ",";
		}
		
		add_inner_comma = false;
		buffer << "\n\t[";
		for (const double &value : row) {
			if (add_inner_comma) {
				buffer << ", ";
			}
			
			buffer << value;
			
			add_inner_comma = true;
		}
		buffer << "]";
		
		add_comma = true;
	}
	buffer << "\n];\n";
	
	add_comma = false;
	buffer << "dist = [";
	for (const std::vector<double> &row : _distance_matrix) {
		if (add_comma) {
			buffer << ",";
		}
		
		add_inner_comma = false;
		buffer << "\n\t[";
		for (const double &value : row) {
			if (add_inner_comma) {
				buffer << ", ";
			}
			
			buffer << value;
			
			add_inner_comma = true;
		}
		buffer << "]";
		
		add_comma = true;
	}
	buffer << "\n];\n";
	
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

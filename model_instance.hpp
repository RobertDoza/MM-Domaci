#ifndef MODEL_INSTANCE_HPP
#define MODEL_INSTANCE_HPP

#include <vector>
#include <ostream>

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

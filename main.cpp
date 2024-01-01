#include <iostream>

#include "generate.hpp"

constexpr double dist_min_value = 0.0;
constexpr double dist_max_value = 30.0;

constexpr double pop_min_value = 0.0;
constexpr double pop_max_value = 100.0;

int main() {
	generate_test_instances({dist_min_value, dist_max_value, pop_min_value, pop_max_value});

	return 0;
}

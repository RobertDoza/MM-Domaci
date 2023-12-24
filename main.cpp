#include <iostream>

#include "generate.hpp"

constexpr int I = 5;
constexpr int J = 5;
constexpr int T = 5;
constexpr int S = 4;
constexpr int p = 3;

constexpr double dist_min_value = 0.0;
constexpr double dist_max_value = 30.0;

constexpr double pop_min_value = 0.0;
constexpr double pop_max_value = 100.0;

int main() {
	generate_test_instance({I, J, T, S, p}, {dist_min_value, dist_max_value, pop_min_value, pop_max_value});

	return 0;
}

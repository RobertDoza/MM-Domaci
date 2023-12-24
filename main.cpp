#include <iostream>

#include "generate.hpp"

constexpr int I = 5;
constexpr int J = 5;
constexpr int T = 5;
constexpr int S = 4;
constexpr int p = 3;

int main() {
	generate_test_instance(I, J, T, S, p);

	return 0;
}

#include <iostream>

#include "model_instance.hpp"

constexpr int I = 5;
constexpr int J = 5;
constexpr int T = 5;
constexpr int S = 4;
constexpr int p = 3;

int main() {
	ModelInstance instance(I, J, T, S, p);
	
	std::cout << instance;

	return 0;
}

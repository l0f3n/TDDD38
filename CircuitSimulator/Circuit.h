#pragma once 

#include <vector>

#include "Component.h"

class Circuit {
	public:
		void simulate(int steps, int print_count, double timestep);
		void add(Component* component);

	private:
		std::vector<Component*> components{};
};

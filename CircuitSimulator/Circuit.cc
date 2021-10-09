#include <iostream>
#include <iomanip>
#include <vector>

#include "Circuit.h"

void Circuit::simulate(int steps, int print_count, double timestep) {
	int interval{static_cast<int>(steps/print_count)};

	for (Component* component : components) {	
		std::cout << std::setw(11) << component->name << " "; 
	}

	std::cout << std::endl;

	for (unsigned i{}; i<components.size(); i++) {	
		std::cout << std::setw(5) << "Volt" << " "; 
		std::cout << std::setw(5) << "Curr" << " "; 
	}

	std::cout << std::endl;

	for (int i{0}; i<steps; i++) {

		for (Component* component : components) {
			component->update(timestep);
		}

		if (i % interval == 0) {

			for (Component* component : components) {
				std::cout << std::setw(5) << std::fixed << std::setprecision(2) << std::showpoint << component->get_voltage() << " "; 
				std::cout << std::setw(5) << std::fixed << std::setprecision(2) << std::showpoint << component->get_current() << " "; 
			}

			std::cout << std::endl;

		}
	}
}

void Circuit::add(Component* component) {
	components.push_back(component);
}

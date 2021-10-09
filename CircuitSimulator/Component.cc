#include <string>

#include "Component.h"

// ==== Component ====

Component::Component(std::string name, Connection& c1, Connection& c2)
	: name{name}, c1{c1}, c2{c2} 
{ }

double Component::get_voltage() {
	return c1.get_voltage() - c2.get_voltage();
}

// ==== Battery ====

Battery::Battery(std::string name, double voltage, Connection& c1, Connection& c2)
	: Component{name, c1, c2}, voltage{voltage} 
{ }

void Battery::update(double timestep) {
	c1.set_voltage(voltage);
	c2.set_voltage(0);
}

double Battery::get_current() {
	return 0;
}

// ==== Resistor ==== 

Resistor::Resistor(std::string name, double resistance, Connection& c1, Connection& c2)
	: Component{name, c1, c2}, resistance{resistance} 
{ }

void Resistor::update(double timestep) {
	double v1{c1.get_voltage()}, v2{c2.get_voltage()};
	if (v1 < v2) {
		double amount = ((v2 - v1) / resistance) * timestep;
		c1.update_charge(amount);
		c2.update_charge(-amount);
	} else {
		double amount = ((v1 - v2) / resistance) * timestep;
		c1.update_charge(-amount);
		c2.update_charge(amount);
	}
}

double Resistor::get_current() {
	return get_voltage() / resistance;
}

// ==== Capacitor ====

Capacitor::Capacitor(std::string name, double capacitance, Connection& c1, Connection& c2)
	: Component{name, c1, c2}, capacitance{capacitance}, charge{}
{ }

void Capacitor::update(double timestep) {
	double v1{c1.get_voltage()}, v2{c2.get_voltage()};
	if (v1 < v2) {
		double amount = capacitance * ((v2 - v1) - charge) * timestep;
		c1.update_charge(amount);
		c2.update_charge(-amount);
		charge += amount;
	} else {
		double amount = capacitance * ((v1 - v2) - charge) * timestep;
		c1.update_charge(-amount);
		c2.update_charge(amount);
		charge += amount;
	}
}

double Capacitor::get_current() {
	return capacitance * (get_voltage() - charge); 
}

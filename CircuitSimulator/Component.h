#pragma once

#include <string>

#include "Connection.h"

class Component {
	public:
		Component(std::string name, Connection& c1, Connection& c2);
		virtual ~Component() = default;

		Component(Component const&) = delete;
		Component(Component &&) = delete;
		Component& operator=(Component const&) = delete;
		Component& operator=(Component &&) = delete;

		virtual void update(double timestep) = 0;
		double get_voltage();
		virtual double get_current() = 0;
		
		const std::string name;

	protected:
		Connection &c1, &c2;
};

class Battery : public Component {
	public:
		Battery(std::string name, double voltage, Connection& c1, Connection& c2);
		~Battery() = default;

		void update(double timestep) override;
		double get_current() override;

	private:
		double voltage{};
};

class Resistor : public Component {
	public:
		Resistor(std::string name, double resistance, Connection& c1, Connection& c2);

		void update(double timestep) override;
		double get_current() override;
	private:
		double resistance{};
};

class Capacitor : public Component {
	public:
		Capacitor(std::string name, double capacitance, Connection& c1, Connection& c2);

		void update(double timestep) override;
		double get_current() override;
	private:
		double capacitance;
		double charge;
};

#pragma once

#include <vector>


class Connection {
	public:
		Connection();

		void update_charge(double charge);
		void set_voltage(double charge);
		double get_voltage() const;

	private:
		double charge{};
};

#include "Connection.h"

Connection::Connection()
	: charge{0}
{}

void Connection::update_charge(double charge) {
	this->charge += charge;
}

void Connection::set_voltage(double voltage) {
	this->charge = voltage;
}

double Connection::get_voltage() const {
	return charge;
}


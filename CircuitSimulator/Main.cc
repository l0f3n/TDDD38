#include <iostream>

#include "Circuit.h"
#include "Component.h"
#include "Connection.h"

int main() {

{
	Circuit c{};
	Connection P{}, R124{}, N{}, R23{};
	c.add(new Battery("Bat", 24, P, N));
	c.add(new Resistor("R1", 6, P, R124));
	c.add(new Resistor("R2", 4, R124, R23));
	c.add(new Resistor("R3", 8, R23, N));
	c.add(new Resistor("R4", 12, R124, N));
	c.simulate(200000, 10, 0.01);
}

	std::cout << std::endl;

{
	Circuit c{};
	Connection P{}, L{}, N{}, R{};
	c.add(new Battery("Bat", 24, P, N));
	c.add(new Resistor("R1", 150, P, L));
	c.add(new Resistor("R2", 50, P, R));
	c.add(new Resistor("R3", 100, R, L));
	c.add(new Resistor("R4", 300, L, N));
	c.add(new Resistor("R5", 250, R, N));
	c.simulate(200000, 10, 0.01);
}

	std::cout << std::endl;

{
	Circuit c{};
	Connection P{}, L{}, N{}, R{};
	c.add(new Battery("Bat", 24, P, N));
	c.add(new Resistor("R1", 150, P, L));
	c.add(new Resistor("R2", 50, P, R));
	c.add(new Capacitor("C3", 1, R, L));
	c.add(new Resistor("R4", 300, L, N));
	c.add(new Capacitor("C5", 0.75, R, N));
	c.simulate(200000, 10, 0.01);
}

}

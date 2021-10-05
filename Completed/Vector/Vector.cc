#include <iostream>
#include <cmath>

#include "Vector.h"

Vector::Vector() : x{}, y{} {};

Vector::Vector(double x, double y) : x{x}, y{y} {};

Vector Vector::operator+(Vector const &o) const {
	return Vector(x+o.x, y+o.y);	
}

void Vector::operator+=(Vector const &o) {
	x += o.x;
	y += o.y;
}

Vector Vector::operator-() const {
	return Vector(-x, -y);
}

Vector Vector::operator-(Vector const &o) const {
	return *this+(-o);	
}

void Vector::operator-=(Vector const &o) {
	x -= o.x;
	y -= o.y;
}


Vector Vector::operator*(double s) const {
	return Vector(s*x, s*y);	
}

Vector operator*(double s, Vector const &o) {
	return o*s; 
}

void Vector::operator*=(double s) {
	x *= s;
	y *= s;
}

Vector Vector::operator/(double s) const {
	return Vector(x/s, y/s);
}

void Vector::operator/=(double s) {
	x /= s;
	y /= s;
}

std::ostream& operator<<(std::ostream &os, Vector const &o) {
	return os << "(" << o.x << ", " << o.y << ")";
}

std::istream& operator>>(std::istream &is, Vector &o) {
	char l, r, c;
	double x, y;
	is >> l >> x >> c >> y >> r;
	
	if (l == '(' && c == ',' && r == ')') {
		o.x = x;
		o.y = y;
	} else {
		std::cin.setstate(std::ios::failbit);
	}

	return is;
}


bool Vector::operator==(Vector const &o) const {
	return x==o.x && y==o.y;
}

bool Vector::operator!=(Vector const &o) const {
	return !(*this==o);
}

double Vector::operator*(Vector const &o) const {
	return x*o.x + y*o.y;
}

double Vector::length() const {
	return sqrt(x*x + y*y);	
}

void test() {
	Vector v{2, 1};
	Vector w{1, 2};

	Vector x{v+w};
	std::cout << x << std::endl;

	x += w;
	std::cout << x << std::endl;

	x = -x;
	std::cout << x << std::endl;

	x = (x-w);
	std::cout << x << std::endl;

	x -= w;
	std::cout << x << std::endl;

	x = x*-2;
	std::cout << x << std::endl;

	x *= 2;
	std::cout << x << std::endl;

	x = x/2;
	std::cout << x << std::endl;

	x /= 2;
	std::cout << x << std::endl;

	std::cout << (x==(v+4*w)) << std::endl;

	std::cout << (x==(v+5*w)) << std::endl;

	std::cout << (x!=(v+4*w)) << std::endl;

	std::cout << (x!=(v+5*w)) << std::endl;

	std::cout << x*Vector{-9, 6} << std::endl;

	std::cout << x.length() << std::endl;

	std::cin >> x;

	std::cout << x << std::endl;
}

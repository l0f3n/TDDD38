#pragma once

#include <iostream>

class Vector {
	public:
		Vector();
		Vector(double x, double y);
		
		// Negate vector
		Vector operator-() const;

		// Add vectors
		Vector operator+(Vector const &o) const;
		void operator+=(Vector const &o);

		// Subtract vectors 
		Vector operator-(Vector const &o) const;
		void operator-=(Vector const &o);

		// Multiply vector with constant
		Vector operator*(double s) const;
		void operator*=(double s);

		// Divide vector with constant
		Vector operator/(double s) const;
		void operator/=(double s);

		// Print vector to stream
		// Read vector from stream
		friend std::ostream& operator<<(std::ostream &os, Vector const &o);
		friend std::istream& operator>>(std::istream &is, Vector &o);

		// Dot product of two vectors
		double operator*(Vector const &o) const;

		// Compare vectors (equal, unequal)
		bool operator==(Vector const &o) const;
		bool operator!=(Vector const &o) const;

		// Get Length
		double length() const;

	private:
		double x{}, y{};	
};

Vector operator*(double s, Vector const &o);

#pragma once

#include <string>
#include <iostream>

class Time {
	public:
		// Constructors
		Time();
		Time(int hours, int minutes, int seconds);

		// Other functions
		bool is_valid() const;
		std::string to_string(bool const period) const;
		bool is_am() const;

		// ==== Operator overloading ====

		// Arithmetic
		//Time operator+(uint32_t const seconds);
		//Time operator-(uint32_t const seconds);
		//Time& operator++(); // Prefix
		//Time operator++(int); // Postfix
		//Time& operator--(); // Prefix
		//Time operator--(int); // Postfix

		// Comparison
		bool operator==(Time const &o) const;
		bool operator!=(Time const &o) const;

		bool operator<(Time const &o) const;
		bool operator<=(Time const &o) const;
		bool operator>(Time const &o) const;
		bool operator>=(Time const &o) const;

		// Stream
		friend std::ostream& operator<<(std::ostream& os, Time const &o);
		friend std::istream& operator>>(std::istream& is, Time &o);

	private:
		int hours;
		int minutes;
		int seconds;
};

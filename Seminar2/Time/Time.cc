#include <iomanip>
#include <iostream>
#include <string>

#include "Time.h"

// Constructors
Time::Time() : hours{}, minutes{}, seconds{} {
}

Time::Time(int hours, int minutes, int seconds) : 
	hours{hours}, minutes{minutes}, seconds{seconds} {
	}

// Other functions

bool Time::is_valid() const {
	if (!(0 <= hours && hours < 24)) return false; 
	if (!(0 <= minutes && minutes < 60)) return false; 
	if (!(0 <= seconds && seconds < 60)) return false; 
	return true;
}

std::string Time::to_string(bool const period) const {
	std::ostringstream oss{};
	oss << std::setw(2) << std::setfill('0') << (period ? hours % 12 : hours);
	oss << ":"; 
	oss << std::setw(2) << std::setfill('0') << minutes;
	oss << ":";
	oss << std::setw(2) << std::setfill('0') << seconds;
	oss << (period ? (is_am() ? " am" : " pm") : "");
	return oss.str();
}

bool Time::is_am() const {
	return hours < 12;
}

// ==== Operator overloading ====

// Arithmetic

Time& Time::operator++() {
	seconds += 1;
	if (seconds == 60) {
		seconds = 0;
		minutes += 1;
		if (minutes == 60) {
			minutes = 0;
			hours += 1;
			if (hours == 24) {
				hours = 0;
			}
		}
	}
	return *this;
}

Time& Time::operator--() {
	seconds -= 1;
	if (seconds == -1) {
		seconds = 59;
		minutes -= 1;
		if (minutes == -1) {
			minutes = 59;
			hours -= 1;
			if (hours == -1) {
				hours = 23;
			}
		}
	}
	return *this;
}

// Comparison
bool Time::operator==(Time const &o) const {
	return (this->seconds == o.seconds
			&& this->minutes == o.minutes
			&& this->hours == o.hours);

}

bool Time::operator!=(Time const &o) const {
	return !(*this==o);
}

bool Time::operator>(Time const &o) const {
	int this_seconds{hours*60*60 + minutes*60 + seconds};
	int other_seconds{o.hours*60*60 + o.minutes*60 + o.seconds};
	return this_seconds > other_seconds;
}

bool Time::operator>=(Time const &o) const {
	int this_seconds{hours*60*60 + minutes*60 + seconds};
	int other_seconds{o.hours*60*60 + o.minutes*60 + o.seconds};
	return this_seconds >= other_seconds;
}

bool Time::operator<(Time const &o) const {
	return !(*this>=o);
}

bool Time::operator<=(Time const &o) const {
	return !(*this>o); 
}

// Stream
std::ostream& operator<<(std::ostream& os, Time const &o) {
	return os << o.to_string(false);
}

std::istream& operator>>(std::istream& is, Time &o) {
	int hours{}, minutes{}, seconds{};

	is >> hours;

	if (!(is.peek() == ':')) {
		is.setstate(std::ios::failbit);
		return is;
	}

	is.ignore(1) >> minutes;

	if (!(is.peek() == ':')) {
		is.setstate(std::ios::failbit);
		return is;
	}

	is.ignore(1) >> seconds;	

	o = Time{hours, minutes, seconds};
	return is;
}


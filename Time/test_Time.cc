#include <iostream>

#include <catch.hpp>

#include "Time.h"

TEST_CASE("Comparison operator overloading") {
	Time t{};

	// Equality
	CHECK( (t == Time{0, 0, 0}) );
	CHECK_FALSE( (t == Time{1, 0, 0}) );

	// Inequality
	CHECK( (t != Time{1, 0, 0}) );
	CHECK_FALSE( (t != Time{0, 0, 0}) );

	Time t1{1, 1, 1};

	// Less then
	CHECK( (t1 < Time{1, 1, 2}) ); 
	CHECK_FALSE( (t1 < Time{1, 1, 1}) ); 
	CHECK_FALSE( (t1 < Time{1, 1, 0}) ); 

	// Less then or equal to
	CHECK( (t1 <= Time{1, 1, 2}) ); 
	CHECK( (t1 <= Time{1, 1, 1}) ); 
	CHECK_FALSE( (t1 < Time{1, 1, 0}) ); 
	CHECK_FALSE( (t1 <= Time{1, 1, 0}) ); 

	// Bigger than
	CHECK( (t1 > Time{1, 1, 0}) ); 
	CHECK_FALSE( (t1 > Time{1, 1, 1}) ); 
	CHECK_FALSE( (t1 > Time{1, 1, 2}) ); 

	// Bigger than or equal to
	CHECK( (t1 >= Time{1, 1, 0}) ); 
	CHECK( (t1 >= Time{1, 1, 1}) ); 
	CHECK_FALSE( (t1 > Time{1, 1, 2}) ); 
	CHECK_FALSE( (t1 >= Time{1, 1, 2}) ); 
}

/*
TEST_CASE("Arithmetic operator overloading") {
	Time t{};
	Time t1{23, 59, 59};

	CHECK( ((++t) == Time{0, 0, 1}) );
	CHECK( ((++t1) == Time{0, 0, 0}) );

	CHECK( ((t + 1) == Time{0, 0, 1}) );
	CHECK( ((t + 60) == Time{0, 1, 0}) );
	CHECK( ((t + 61) == Time{0, 1, 1}) );
	CHECK( ((t + 3600) == Time{1, 0, 0}) );
	CHECK( ((t + 3601) == Time{1, 0, 1}) );
	CHECK( ((t1 + 1) == Time{0, 0, 0}) );
	CHECK( ((t1 + 2) == Time{0, 0, 1}) );

	CHECK( ((t1 - 59) == Time{23, 59, 0}) );
	CHECK( ((t1 - 60) == Time{23, 58, 59}) );
	CHECK( ((t1 - 3600) == Time{22, 59, 59}) );
}
*/

TEST_CASE("Stream functions") {
	std::ostringstream oss1{};
	oss1 << Time{9, 4, 2};
	CHECK( (oss1.str() == "09:04:02") );

	std::ostringstream oss2{};
	oss2 << Time{22, 23, 24};
	CHECK( (oss2.str() == "22:23:24") );

	Time t{};

	std::istringstream iss1{"04:53:26"};
	iss1 >> t; 
	CHECK_FALSE( (iss1.fail()) );
	CHECK( (t.to_string(false) == "04:53:26") );

	std::istringstream iss2{"03 23:22"};
	iss2 >> t; 
	CHECK( (iss2.fail()) );
	CHECK( (t.to_string(false) == "04:53:26") );
}

TEST_CASE("Other functions") {

	// ==== is_valid() ====

	CHECK( (Time{}.is_valid()) );
	CHECK( (Time{0, 0, 0}.is_valid()) );

	// Hours
	CHECK( (Time{1, 0, 0}.is_valid()) );
	CHECK( (Time{23, 0, 0}.is_valid()) );
	CHECK_FALSE( (Time{24, 0, 0}.is_valid()) );
	CHECK_FALSE( (Time{25, 0, 0}.is_valid()) );
	CHECK_FALSE( (Time{-1, 0, 0}.is_valid()) );

	// Minutes
	CHECK( (Time{0, 1, 0}.is_valid()) );
	CHECK( (Time{0, 59, 0}.is_valid()) );
	CHECK_FALSE( (Time{0, 60, 0}.is_valid()) );
	CHECK_FALSE( (Time{0, 61, 0}.is_valid()) );
	CHECK_FALSE( (Time{0, -1, 0}.is_valid()) );

	// Seconds
	CHECK( (Time{0, 0, 1}.is_valid()) );
	CHECK( (Time{0, 0, 59}.is_valid()) );
	CHECK_FALSE( (Time{0, 0, 60}.is_valid()) );
	CHECK_FALSE( (Time{0, 0, 61}.is_valid()) );
	CHECK_FALSE( (Time{0, 0, -1}.is_valid()) );

	// ==== to_string() ====

	CHECK( (Time{}.to_string(false) == "00:00:00") );

	CHECK( (Time{23, 20, 43}.to_string(false) == "23:20:43") );
	CHECK( (Time{4, 7, 2}.to_string(false) == "04:07:02") );

	CHECK( (Time{}.to_string(true) == "00:00:00 am") );

	CHECK( (Time{7, 5, 8}.to_string(true) == "07:05:08 am") );
	CHECK( (Time{11, 37, 42}.to_string(true) == "11:37:42 am") );

	CHECK( (Time{13, 40, 6}.to_string(true) == "01:40:06 pm") );
	CHECK( (Time{20, 20, 20}.to_string(true) == "08:20:20 pm") );

	// ==== is_am() ==== 

	CHECK_FALSE( (Time{23, 59, 59}.is_am()) );
	CHECK( (Time{0, 0, 0}.is_am()) );
	CHECK( (Time{0, 0, 1}.is_am()) );

	CHECK( (Time{6, 23, 47}.is_am()) );
	CHECK( (Time{9, 59, 0}.is_am()) );
	CHECK( (Time{10, 33, 33}.is_am()) );

	CHECK( (Time{11, 59, 59}.is_am()) );
	CHECK_FALSE( (Time{12, 0, 0}.is_am()) );
	CHECK_FALSE( (Time{12, 0, 1}.is_am()) );

	CHECK_FALSE( (Time{16, 33, 57}.is_am()) );
	CHECK_FALSE( (Time{19, 49, 1}.is_am()) );
	CHECK_FALSE( (Time{20, 23, 43}.is_am()) );
}

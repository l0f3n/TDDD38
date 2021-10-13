#include <iostream>
#include <stdint.h>

#include <catch.hpp>

#include "LinkedList.h"

TEST_CASE("Regular functions") {
	LinkedList l{};

	l.insert(1);
	l.insert(2);
	l.insert(3);

	LinkedList l1{l};	

	l.insert(0);
	l1.insert(4);

	l.remove(3);
	l1.remove(1);

	l.print();
	l1.print();

	LinkedList l2{LinkedList{1}};

	l2.insert(5);

	l2.print();
}

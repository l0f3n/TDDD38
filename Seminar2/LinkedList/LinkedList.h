#pragma once

#include <stdint.h>
#include <iostream>

class LinkedList {
	public:
		LinkedList(); // Default constructor
		LinkedList(int value); // Default constructor
		LinkedList(LinkedList const &o); // Copy constructor
		LinkedList(LinkedList &&o); // Move constructor

		~LinkedList(); // Destructor

		LinkedList& operator=(LinkedList const &o); // Copy assignment
		LinkedList& operator=(LinkedList &&o); // Move assignment

		void insert(int value);
		void remove(uint32_t index);
		void remove(int value);
		void print();
		void at(uint32_t index);

	private:
		typedef struct Node {
			int value;
			struct Node *next;
		} Node;

		Node *start;
};


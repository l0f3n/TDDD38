#include <iostream>
#include <stdint.h>

#include "LinkedList.h"

LinkedList::LinkedList() : start{new Node{0, nullptr}} {
	std::cout << "Default constructor" << std::endl;
}

LinkedList::LinkedList(int value) : start{new Node{0, new Node{value, nullptr}}} {
	std::cout << "Default constructor with value" << std::endl;
}

LinkedList::LinkedList(LinkedList const &o) : start{new Node{0, nullptr}} {
	std::cout << "Copy constructor" << std::endl;
	Node *curr = start;
	Node *o_curr = o.start->next;
	while (o_curr != nullptr) {
		curr->next = new Node{o_curr->value, nullptr};	
		curr = curr->next;
		o_curr = o_curr->next;
	}
}

LinkedList::LinkedList(LinkedList &&o) : start{new Node{0, nullptr}} {
	std::cout << "Move constructor" << std::endl;
	Node *curr = start;
	Node *o_curr = o.start->next;
	while (o_curr != nullptr) {
		curr->next = o_curr;	
		curr = curr->next;
		o_curr = o_curr->next;
	}
}

LinkedList::~LinkedList() {
	std::cout << "Destructor" << std::endl;
	Node *curr = start;
	Node *next = start->next;
	while(curr != nullptr) {
		delete curr;
		curr = next;
		if (next != nullptr) next = next->next;
	}
}

void LinkedList::insert(int value) {
	Node *previous = start;
	Node *current = start->next;
	while (current != nullptr && current->value < value) {
		previous = current;
		current = current->next;
	}
	previous->next = new Node{value, current};
}

void LinkedList::remove(uint32_t index) {
	Node *previous = start;
	Node *current = start->next; 
	while (current != nullptr && (index--) > 0) {
		previous = current;
		current = current->next;	
	}
	previous->next = current->next;
	delete current;
}

void LinkedList::remove(int value) {
	Node *previous = start;
	Node *current = start->next; 
	while (current != nullptr && current->value != value) {
		previous = current;
		current = current->next;	
	}
	if (current != nullptr) {
		previous->next = current->next;
		delete current;
	}
}

void LinkedList::print() {
	Node *current = start->next;
	if (current == nullptr) return;
	do {
		std::cout << "(" << current->value << ")" << "->";
	} while ((current = current->next) != nullptr);
	std::cout << std::endl;
}


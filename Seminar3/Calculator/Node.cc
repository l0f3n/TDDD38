#include <iostream>
#include <iomanip>

#include "Node.h"

/*
  Implement the functionality of the Node hierarchy
*/

// ==== Node ====

Node::~Node() {}

// ==== Number ====

Number::Number(double value) : value{value} {

}

double Number::evaluate() const {
	return value;
}

void Number::print(std::ostream& os) const {
	os << value;
}

void Number::print_tree(std::ostream &os, int depth) const {
	os << std::setw(depth) << value;
}

Number* Number::clone() const {
	return new Number{value};
}

// ==== Operator ====

Operator::Operator(Node* lhs, Node* rhs) : lhs{lhs}, rhs{rhs} {
	
}

Operator::~Operator() {
	delete lhs;
	delete rhs; 
}

void Operator::print_helper(std::ostream& os, bool parenthesis, char op) const {
	if (parenthesis) {
		Addition *l{dynamic_cast<Addition*>(lhs)};
		if (l != nullptr) {
			os << "(";
			lhs->print(os);
			os << ")";
		} else {
			lhs->print(os);
		}
	} else {
		lhs->print(os);
	}

	os << op; 

	if (parenthesis) {
		Addition *r{dynamic_cast<Addition*>(rhs)};
		if (r != nullptr) {
			os << "(";
			rhs->print(os);
			os << ")";
		} else {
			rhs->print(os);
		}
	} else {
		rhs->print(os);
	}
}

void Operator::print_tree_helper(std::ostream& os, int depth, char op) const {
	lhs->print_tree(os, depth+3);
	os << std::endl << std::setw(depth+2) << "/" << std::endl;
	os << std::setw(depth+1) << op << std::endl;
	os << std::setw(depth+2) << "\\" << std::endl;
	rhs->print_tree(os, depth+3);
}

// ==== Addition ====

Addition::Addition(Node* lhs, Node* rhs) : Operator(lhs, rhs) {}

double Addition::evaluate() const {
	double lhs{this->lhs->evaluate()};	
	double rhs{this->rhs->evaluate()};	
	return lhs + rhs;
}

void Addition::print(std::ostream& os) const {
	Operator::print_helper(os, false, '+');
}

void Addition::print_tree(std::ostream& os, int depth) const {
	Operator::print_tree_helper(os, depth, '+');
}

Addition* Addition::clone() const {
	Node *rhs = this->rhs->clone();
	Node *lhs = this->lhs->clone();
	return new Addition(rhs, lhs);
}

// ==== Subtraction ====

Subtraction::Subtraction(Node* lhs, Node* rhs) : Addition(lhs, rhs) {}

double Subtraction::evaluate() const {
	double lhs{this->lhs->evaluate()};	
	double rhs{this->rhs->evaluate()};	
	return lhs - rhs;
}

void Subtraction::print(std::ostream& os) const {
	Operator::print_helper(os, false, '-');
}

void Subtraction::print_tree(std::ostream& os, int depth) const {
	Operator::print_tree_helper(os, depth, '-');
}

Subtraction* Subtraction::clone() const {
	Node *rhs = this->rhs->clone();
	Node *lhs = this->lhs->clone();
	return new Subtraction(rhs, lhs);
}

// ==== Multiplication ====

Multiplication::Multiplication(Node* lhs, Node* rhs) : Operator(lhs, rhs) {}

double Multiplication::evaluate() const {
	double lhs{this->lhs->evaluate()};	
	double rhs{this->rhs->evaluate()};	
	return lhs * rhs;
}

void Multiplication::print(std::ostream& os) const {
	Operator::print_helper(os, true, '*');
}

void Multiplication::print_tree(std::ostream& os, int depth) const {
	Operator::print_tree_helper(os, depth, '*');
}

Multiplication* Multiplication::clone() const {
	Node *rhs = this->rhs->clone();
	Node *lhs = this->lhs->clone();
	return new Multiplication(rhs, lhs);
}

// ==== Division ====

Division::Division(Node* lhs, Node* rhs) : Multiplication(lhs, rhs) {}

double Division::evaluate() const {
	double lhs{this->lhs->evaluate()};	
	double rhs{this->rhs->evaluate()};	
	return lhs / rhs;
}

void Division::print(std::ostream& os) const {
	Operator::print_helper(os, true, '/');
}

void Division::print_tree(std::ostream& os, int depth) const {
	Operator::print_tree_helper(os, depth, '/');
}

Division* Division::clone() const {
	Node *rhs = this->rhs->clone();
	Node *lhs = this->lhs->clone();
	return new Division(rhs, lhs);
}

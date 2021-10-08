#include "Expression.h"

#include <stdexcept>
#include <ostream>

Expression::Expression(Node* root) : root{root} {}

Expression::~Expression() {
	delete root;
}

double Expression::evaluate() const {
	return root->evaluate();
}

void Expression::print_tree(std::ostream& os) const {
	root->print_tree(os, 0);
}

/* For part B */

void Expression::print(std::ostream& os) const
{
    root->print(os);
}


/* For part C */

void Expression::expand()
{
    throw std::invalid_argument{"--expand is unimplemented"};
}


/*
  Implement the classes:
  - Node

  - Number

  - Operator

  - Addition
  - Subtraction
  - Multiplication
  - Division

  Node should have the following (pure virtual) members:
  - double evaluate()
    + Calculate the expression stored in 'this'
  - void print(std::ostream& os)
    + print the expression represented in 'this'
  - void print_tree(std::ostream& os, int depth)
    + print a textual representation of the expression tree
  - Node* clone()
    + return a a new instance of the expression stored in 'this'
 */

#include <iostream>

class Node {
	public:
		virtual ~Node() = 0;
		virtual double evaluate() const = 0;
//		virtual void print(std::ostream& os) = 0;
		virtual void print_tree(std::ostream& os, int depth) const = 0;
		virtual Node* clone() const = 0;
};

class Number : public Node {
	public:
		Number(double value);
		~Number() override = default;
		double evaluate() const override;
		void print_tree(std::ostream& os, int depth) const override;
		Number* clone() const override;
	private:
		double value;
};

class Operator : public Node {
	public:
		Operator(Node* lhs, Node* rhs);
		~Operator() override;

	protected:
		void print_helper(std::ostream& os, int depth, char op) const;
		Node *lhs, *rhs;
};

class Addition : public Operator {
	public:
		Addition(Node* lhs, Node* rhs);
		double evaluate() const override;
		void print_tree(std::ostream& os, int depth) const override;
		Addition* clone() const override;
};

class Subtraction : public Operator {
	public:
		Subtraction(Node* lhs, Node* rhs);
		double evaluate() const override;
		void print_tree(std::ostream& os, int depth) const override;
		Subtraction* clone() const override;
};

class Multiplication : public Operator {
	public:
		Multiplication(Node* lhs, Node* rhs);
		double evaluate() const override;
		void print_tree(std::ostream& os, int depth) const override;
		Multiplication* clone() const override;
};

class Division : public Operator {
	public:
		Division(Node* lhs, Node* rhs);
		double evaluate() const override;
		void print_tree(std::ostream& os, int depth) const override;
		Division* clone() const override;
};

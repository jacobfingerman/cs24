#ifndef NODES_H
#define NODES_H

#include "AST.h"
#include <cmath>
#include <stdexcept>

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.

class NumNode : public AST {
	double val;
public:
	NumNode(double num);
	// Virtual destructor:
	~NumNode() {}

	// Member functions for output:
	std::string prefix()  const;
	std::string postfix() const;
	double      value()   const;
};

class ExpNode : public AST {
	char val;
	AST* left;
	AST* right;
public:
	ExpNode(char exp, AST* r = nullptr, AST* l = nullptr);
	// Virtual destructor:
	~ExpNode();

	// Member functions for output:
	std::string prefix()  const;
	std::string postfix() const;
	double      value()   const;
};

#endif

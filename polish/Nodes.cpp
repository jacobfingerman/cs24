#include "Nodes.h"
#include <cmath>
#include <cstddef>
// Implement your AST subclasses' member functions here.


// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();


// ==============   NumNode   =====================================
NumNode::NumNode(double num) { val = num; }
NumNode::~NumNode() { return; }

std::string NumNode::prefix()  const { return std::to_string(val); }
std::string NumNode::postfix() const { return std::to_string(val); }
double      NumNode::value()   const { return val; }

// ==============   ExpNode   =====================================

ExpNode::ExpNode(char exp, AST* r, AST* l) { val = exp; left = l; right = r; }
ExpNode::~ExpNode() { return; }

std::string ExpNode::prefix()  const { 
	if (val == '~') return "~ " + right->prefix();
	else return std::string(1, val) + " " + left->prefix() + " " + right->prefix();
}
std::string ExpNode::postfix() const {
	if (val == '~') return right->postfix() + " ~";
	else return left->postfix() + " " + right->postfix() + " " + std::string(1, val);
}
double      ExpNode::value()   const {
	if (!right) throw std::runtime_error("invalid token");
	else if (!left && val != '~') throw std::runtime_error("invalid token");
	else if ( left && val == '~') throw std::runtime_error("invalid token");

	switch (val) {
	case '+': // add
		return left->value() + right->value();
		break;

	case '-': // subtract
		return left->value() - right->value();
		break;

	case '*': // multiply
		return left->value() * right->value();
		break;
		
	case '/': // divide
		if (right->value() == 0) throw std::runtime_error("Division by zero.");
		else return left->value() / right->value();
		break;

	case '%': // modulus
		if (right->value() == 0) throw std::runtime_error("Division by zero.");
		else return fmod(left->value(), right->value());
		break;

	case '~': // negate
		return right->value() * -1;
		break;

	default:
		throw std::runtime_error("invalid token");
	}
}

#include "AST.h"
#include "Nodes.h"
#include "Stack.h"
#include <sstream>

AST* AST::parse(const std::string& expression) {
	char exp[5] = { '+', '-', '*', '/', '%' };

	Stack stack;
	std::istringstream stream(expression);
	std::string token;

	LOOP: while (stream >> token) {
		// Expression node case (loops through operators)
		if (token.length() == 1) {
			for (int i = 0; i < 5; i++) {
				if (token[0] == exp[i]) {
					AST* right = stack.pop();
					AST* left = stack.pop();
					if (!right || !left) {
						delete right;
						delete left;
						throw std::runtime_error("Not enough operands.");
					}

					else stack.push(new ExpNode(token[0], right, left));

					goto LOOP;
				}
			}
			if (token[0] == '~') {
				AST* right = stack.pop();
				if (!right) throw std::runtime_error("Not enough operands.");
					

				else stack.push(new ExpNode(token[0], right));

				goto LOOP;
			}

		}

		// Checks if 2 decimals or weird characters after 1st char (could be +/-)
		bool dot = false;
		for (std::string::iterator it = token.begin() + 1; it != token.end(); ++it) {
			if (*it == '.') { if (!(dot ^= 1)) throw std::runtime_error("Invalid token: " + token);}
			else if (*it > '9' || *it < '0') throw std::runtime_error("Invalid token: " + token);
		}

		// If 1st char is +/-, works fine, but alphabet doesn't work
		try { stack.push(new NumNode(stod(token))); }
		catch (...) {
			stack.shred();
			throw std::runtime_error("Invalid token: " + token);
		}
	}

	if (stack.size() == 0) throw std::runtime_error("No input.");
	if (stack.size() > 1) {
		stack.shred();
		throw std::runtime_error("Too many operands.");
	}

	return stack.top();
}

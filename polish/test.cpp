#include "AST.h"
#include "Nodes.h"
#include "Stack.h"
#include <iostream>


// If you want a different main function, write it here!
// This file won't be graded - do whatever you want.


int main() {
	
	std::string st = "+12.2 2.8 + 5 4 + 2 / *";

	//std::string st = "0";

	AST* ast = nullptr;

	ast = AST::parse(st);

	std::cout << ast->prefix() << "\n";
	std::cout << ast->postfix() << "\n";
	std::cout << ast->value() << "\n";




  return 0;
}

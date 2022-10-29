#ifndef STACK_H
#define STACK_H

#include "AST.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

struct stackNode{
	AST* node;
	stackNode* previous;

	stackNode(stackNode* stNode, AST* ASNode) {
		previous = stNode;
		node = ASNode;
	}
};

class Stack {
	stackNode* head;
	size_t count;

public:
	Stack();
	~Stack();

	bool empty() const;
	size_t size() const;
	AST* top() const;

	bool push(AST* newNode);
	AST* pop();

};

#endif

#include "Stack.h"

// Implement your Stack member functions here.

Stack::Stack() {
	head = nullptr;
	count = 0;
}

Stack::~Stack() {
	while (!empty()) { pop(); }
}


bool Stack::empty() const { return (count == 0); }
size_t Stack::size() const { return count; }
AST* Stack::top() const { return head->node;  }

bool Stack::push(AST* newNode) {
	head = new stackNode(head, newNode);
	
	count += 1;
	return 1;


}
AST* Stack::pop() {
	if (count == 0) return nullptr;
	else {
		stackNode temp = *(head);
		delete head;

		head = temp.previous;

		count -= 1;
		return temp.node;
	}
}
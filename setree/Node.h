#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdexcept>

// Use this file to declare your Node type.
// Implement Node member functions and helper functions in Node.cpp.

class Node {
	Node* left;
	Node* right;
	std::string value;
	size_t count;

public:
	Node(std::string val, size_t num = 0);

	size_t children() const;
	bool connected(const std::string& str) const;
	size_t getHeight(size_t depth=0) const;

	void printChild(size_t branches) const;
	void clearChild();

	Node* search(const std::string& str, bool sizeChange = false, bool adding = true);
	const std::string& index(size_t pos) const;

	size_t addNode(std::string str);
	size_t remNode(const std::string& str);
	void upNode();
	

	Node* clone();
};

#endif

#include "List.h"
#include <iostream>
#include <stdexcept>

Node* incNode(Node* current, size_t steps)  {
	// Returns node n steps later
	if (current == nullptr) throw std::out_of_range("index is out of range");
	else if (steps == 0) {
		return current;
	}
	else return incNode(current->next, steps - 1);
}

void printNode(Node* current, bool reverse = false) {
	// Recursive print across nodes
	// If reverse, prints after the call, so inner nodes get printed first
	if (current == nullptr) return;
	else if (current->next != nullptr) {
		if (!reverse) std::cout << current->data << ", ";
		printNode(current->next, reverse);
		if (reverse) std::cout << ", " << current->data;
	}
	else {
		std::cout << current->data;
	}
	return;
}

Node* alphNode(Node* current, std::string str) {
	// Finds node position of ascii order for string
	// NOTE: requires list to be sorted asciibetically
	if (current == nullptr || current->next == nullptr) return current;
	else if (current->next->data < str) return alphNode(current->next, str);
	else return current;
}

Node* strNode(Node* current, std::string str) {
	// Finds node left of specific string
	if (current == nullptr || current->next == nullptr) return current;
	else if (current->next->data != str) return alphNode(current->next, str);
	else return current;
}

Node* delNode(Node* current, std::string str, size_t* total) {
	// Deletes nodes until they change string value
	// Then returns changed node pointer
	if (current == nullptr) return nullptr;
	else if (current->data == str) {
		Node* rightNode = current->next;
		delete current;
		*(total) += 1;

		return delNode(rightNode, str, total);
	}
	else return current;
}


List::List() {
	//Initializes empty list
	head = nullptr;
}

List::List(const List& other) {
	//Copy linked list
	//NOTE: assumes asciibetical order
	if (other.head == nullptr) {
		head = nullptr;
		return;
	}

	Node* oNode = other.head;
	Node* newNode = new Node;

	head = newNode;
	newNode->data = oNode->data;
	oNode = oNode->next;

	while (oNode != nullptr) {
		newNode->next = new Node;
		newNode = newNode->next;
		newNode->data = oNode->data;
		oNode = oNode->next;
	}

	newNode->next = nullptr;
}

List::List(List&& other) {
	//Move linked list
	head = other.head;
	other.head = nullptr;
}

List::~List() {
	//Destroy linked list
	Node* newHead;
	while (head != nullptr) {
		newHead = head->next;
		delete head;
		head = newHead;
	}
}



size_t             List::count() const {
	//Loop through list until the end and count the number of times
	size_t total = 0;
	Node* current = head;
	while (current != nullptr) {
		current = current->next;
		total += 1;
	}
	return total;
}

void               List::insert(const std::string& value) {
	// Finds position of node before it asciibetically
	// Then old steals next value and points old to new
	Node* newNode = new Node;
	Node* oldNode = alphNode(head, value);

	newNode->data = value;



	if (oldNode == head) {

		if (oldNode == nullptr || head->data > value) {
			head = newNode;
			newNode->next = oldNode;
		}
		else {
			newNode->next = oldNode->next;
			oldNode->next = newNode;
		}
	}
	else {
		newNode->next = oldNode->next;
		oldNode->next = newNode;
	}

	return;
}

const std::string& List::lookup(size_t index) const {
	// Loops through list until either nullptr is found or looped index times
	return incNode(head, index)->data;
}

void               List::print(bool reverse) const {
	std::cout << "[";
	printNode(head, reverse);
	std::cout << "]" << "\n";
}

std::string        List::remove(size_t index) {
	if (index == 0) {
		// Changes head to next node in the chain and deletes old head
		if(head == nullptr) throw std::out_of_range("index is out of range");

		Node* newHead = head->next;
		std::string removed = head->data;
		
		delete head;

		head = newHead;
		return removed;
	}
	else {
		// Links left node to right node and deletes middle
		Node* leftNode = incNode(head, index - 1);
		if (leftNode->next == nullptr) throw std::out_of_range("index is out of range");

		Node* midNode = leftNode->next;

		std::string removed = midNode->data;
		leftNode->next = midNode->next;

		delete midNode;
		return removed;
	}
}

size_t             List::remove(const std::string& value) {
	if (head == nullptr) return 0;
	
	size_t total = 0;
	if (head->data == value) {
		// Prunes head nodes if value is at front
		Node* temp;
		while (head->data == value) {
			total += 1;

			temp = head->next;
			delete head;
			head = temp;

			if (head == nullptr) break;
		}
	}
	else {
		// Finds the node left of the first value 
		// Then deletes nodes until value changes and links old to new node
		Node* current = strNode(head, value);
		current->next = delNode(current->next, value, &total);
	}

	
	return total;
}
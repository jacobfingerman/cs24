#include "Node.h"

void nullTree(size_t branches) {
	if (branches > 0) {
		std::cout << "(";
		nullTree(branches - 1);
		std::cout << " ";
	}

	std::cout << "-";

	if (branches > 0) {
		std::cout << " ";
		nullTree(branches - 1);
		std::cout << ")";
	}
}


Node::Node(std::string val, size_t num) {
	value = val;
	left = nullptr;
	right = nullptr;
	count = num;
}


size_t Node::children() const { return count; }
bool Node::connected(const std::string& str) const {
	// Checks if a value is attached to a parent node
	if (str > value && right != nullptr) return true;
	else if (str < value && left != nullptr) return true;
	else return false;
}
size_t Node::getHeight(size_t depth) const {
	// Finds the depth of the lowest node
	if (left == nullptr) {
		if (right == nullptr) return depth;
		else return right->getHeight(depth + 1);
	}
	else if (right == nullptr) return left->getHeight(depth + 1);
	else {
		size_t r = right->getHeight(depth + 1);
		size_t l = left->getHeight(depth + 1);
		return (r > l) ? r : l;
	}
}



void Node::printChild(size_t branches) const {
	// Prints children recursively
	if (branches > 0) {
		std::cout << "(";
		if (left == nullptr) nullTree(branches - 1);
		else left->printChild(branches - 1);
		std::cout << " ";
	}

	std::cout << value;

	if (branches > 0) {
		std::cout << " ";
		if (right == nullptr) nullTree(branches - 1);
		else right->printChild(branches - 1);
		std::cout << ")";
	}
}

void Node::clearChild() {
	// Removes all children of a node
	// NOTE: doesn't automatically update count
	if (right != nullptr) {
		right->clearChild();
		delete right;
	}

	if (left  != nullptr)	{
		left->clearChild();
		delete left;
	}


}



Node* Node::search(const std::string& str, bool sizeChange, bool adding) {
	// Finds node above prospective value node
	// Either adds or subtracts from size if tree changing
	if (str > value) {
		if (sizeChange) count = (adding) ? count + 1 : count - 1;

		if (right == nullptr) return this;
		else if (right->value == str) return this;

		else return right->search(str, sizeChange, adding);
	}
	else if (str < value) {
		if (sizeChange) count = (adding) ? count + 1 : count - 1;

		if (left == nullptr) return this;
		else if (left->value == str) return this;

		else return left->search(str, sizeChange, adding);
	}
	else return nullptr;
}

const std::string& Node::index(size_t pos) const {
	// Finds node at given "index"
	if (left != nullptr) {
		if (pos <= left->count) return left->index(pos);
		else if (pos == 1 + left->count) return value;
		else return right->index(pos - left->count - 2);
	}
	else if (pos == 0) return value;
	else return right->index(pos - 1);
	
}



size_t Node::addNode(std::string str) {
	// Adds node as child to parent
	// NOTE: does not update counts
	if (str > value) {
		if (right != nullptr) return 0;

		right = new Node(str);
		return 1;
	}
	else {
		if (left != nullptr) return 0;

		left = new Node(str);
		return 1;
	}
}

size_t Node::remNode(const std::string& str) {
	// Removes node based on children
	if (left == nullptr && right == nullptr) return 0; // Not in set
	else if (str > value) {
		// Right node
		if (right->right == nullptr) {
			if (right->left == nullptr) {
				// No children just deletes node
				delete right;
				right = nullptr;
			}
			else {
				// Replaces with left child if only left
				Node* temp = right->left;
				delete right;
				right = temp;
			}
		}
		else if (right->left == nullptr) {
			// Replaces with right child if only right
			Node* temp = right->right;
			delete right;
			right = temp;
		}
		else right->upNode(); // Two children case

	}

	else {
		// Left node
		if (left->right == nullptr) {
			if (left->left == nullptr) {
				// No children just deletes node
				delete left;
				left = nullptr;
			}
			else {
				// Replaces with left child if only left
				Node* temp = left->left;
				delete left;
				left = temp;
			}
		}
		else if (right->left == nullptr) {
			// Replaces with right child if only right
			Node* temp = left->right;
			delete left;
			left = temp;
		}
		else left->upNode(); // Two children case

	}

	return 1;
}

void Node::upNode() {
	// Replaces node with next valid node in the position
	// Then cleans up the valid node's old position
	if (left == nullptr) {
		value = right->value;
		left = right->left;

		Node* rTemp = right->right;
		delete right;
		right = rTemp;
		return;
	}
	Node* current = left;

	if (current->right == nullptr) {
		value = current->value;
		left = current->left;
		delete current;
	}
	else {
		while (current->right->right != nullptr) { current = current->right; }

		value = current->right->value;
		Node* temp = current->right->left;
		delete current->right;
		current->right = temp;
	}
}



Node* Node::clone() {
	Node* newRoot = new Node(value, count);

	if (left  != nullptr) newRoot->left  = left->clone();
	if (right != nullptr) newRoot->right = right->clone();

	return newRoot;
}
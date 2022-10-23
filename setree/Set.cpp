#include "Set.h"

Set::Set() {
	mRoot = nullptr;
}


Set::Set(const Set& other) {
	if (other.mRoot) mRoot = other.mRoot->clone();
	else mRoot = nullptr;
}

Set::Set(Set&& other) {
	mRoot = other.mRoot;
	other.mRoot = nullptr;
}

Set::~Set() {
	clear();
}


size_t Set::count() const {
	if (mRoot == nullptr) return 0;
	return mRoot->children() + 1;
}

size_t Set::clear() {
	// Removes all children of node then the node
	if (mRoot == nullptr) return 0;

	size_t size = mRoot->children();

	mRoot->clearChild();
	delete mRoot;

	mRoot = nullptr;
	return size + 1;
}

size_t Set::insert(const std::string& value) {
	// Insert value on tree if new
	if (mRoot == nullptr) { 
		mRoot = new Node(value);
		return 1;
	}

	Node* parent = mRoot->search(value, true);

	if (parent == nullptr) return 0;


	if (parent->addNode(value)) return 1;
	else {
		mRoot->search(value, true, false);
		return 0;
	}

}

void Set::print() const {
	// Finds height then prints child
	// Slowing down print with height check 
	//	seems more practical than dealing with keeping track
	//  and slowing down the actual data 
	if (mRoot == nullptr) std::cout << "-";
	else mRoot->printChild();

	std::cout << "\n";
}

bool Set::contains(const std::string& value) const {
	// Finds potential parent node of value and checks whether its connected
	if (mRoot == nullptr) return false;
	
	Node* parent = mRoot->search(value);
	if (!parent) return true;

	return parent->connected(value);
}

const std::string& Set::lookup(size_t n) const {
	if (mRoot == nullptr || n >= count()) throw std::out_of_range("index is out of range");

	return mRoot->index(n);
}

size_t Set::remove(const std::string& value) {;
	if (mRoot == nullptr) return 0;

	std::cout << value << ": " << mRoot->children() << "\n";

	Node* parent = mRoot->search(value, true, false);
	if (parent == nullptr) {
		if (mRoot->children() == 0) {
			delete mRoot;
			mRoot = nullptr;
			return 1;
		}
		else {
			mRoot->upNode();
			return 1;
		}
	}
	else if (parent->remNode(value)) return 1;
	else {
		mRoot->search(value, true);
		return 0;
	}
}

void Set::debug() { std::cout << ">:("; }

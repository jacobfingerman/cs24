#include "Helpers.h"
#include <stdexcept>


#include<iostream>

// ================================================
// ====== HEAP      ===============================
// ================================================

// ====== Handling ================================

Heap::Heap(size_t capacity) {
	mData = new Entry[capacity];
	mCapacity = capacity;
	mCount = 0;
}

Heap::Heap(const Heap& other) {
	mCapacity = other.mCapacity;
	mCount = other.mCount;

	mData = new Entry[other.mCapacity];

	for (size_t i = 0; i < mCount; i++) {
		mData[i] = other.mData[i];
	}
}

Heap::Heap(Heap&& other) {
	mCapacity = other.mCapacity;
	mCount = other.mCount;

	mData = other.mData;
	other.mData = nullptr;
}

Heap::~Heap() {
	delete[] mData;
}


// ====== Functions ===============================
size_t       Heap::capacity() const { return mCapacity; }
size_t       Heap::count() const { return mCount; }



const Heap::Entry& Heap::lookup(size_t index) const {
	if (index >= mCount) throw std::out_of_range("index is out of range");
	return mData[index];
}


Heap::Entry  Heap::pop() {
	if (mCount == 0) throw std::underflow_error("no items");

	Entry popped = mData[0];

	mData[0] = mData[mCount - 1];
	mCount -= 1;

	// Perc
	size_t i = 0;
LOOP:
	if (2 * i + 1 < mCount && mData[i].score < mData[2 * i + 1].score) {
		if (2 * i + 2 < mCount && mData[2 * i + 1].score < mData[2 * i + 2].score) {
			Entry temp = mData[i];
			mData[i] = mData[2 * i + 2];
			mData[2 * i + 2] = temp;
			i = 2 * i + 2;
			goto LOOP;
		}

		Entry temp = mData[i];
		mData[i] = mData[2 * i + 1];
		mData[2 * i + 1] = temp;
		i = 2 * i + 1;
		goto LOOP;
	}
	else if (2 * i + 2 < mCount && mData[i].score < mData[2 * i + 2].score) {
		Entry temp = mData[i];
		mData[i] = mData[2 * i + 2];
		mData[2 * i + 2] = temp;
		i = 2 * i + 2;
		goto LOOP;
	}

	return popped;
}


Heap::Entry  Heap::pushpop(Star star, float score) {
	if (mCount == 0) throw std::underflow_error("no items");

	Entry popped = mData[0];

	Entry newEntry;
	newEntry.star = star;
	newEntry.score = score;

	mData[0] = newEntry;

	// Perc
	size_t i = 0;
LOOP:
	if (2 * i + 1 < mCount && mData[i].score < mData[2 * i + 1].score) {
		if (2 * i + 2 < mCount && mData[2 * i + 1].score < mData[2 * i + 2].score) {
			Entry temp = mData[i];
			mData[i] = mData[2 * i + 2];
			mData[2 * i + 2] = temp;
			i = 2 * i + 2;
			goto LOOP;
		}

		Entry temp = mData[i];
		mData[i] = mData[2 * i + 1];
		mData[2 * i + 1] = temp;
		i = 2 * i + 1;
		goto LOOP;
	}
	else if (2 * i + 2 < mCount && mData[i].score < mData[2 * i + 2].score) {
		Entry temp = mData[i];
		mData[i] = mData[2 * i + 2];
		mData[2 * i + 2] = temp;
		i = 2 * i + 2;
		goto LOOP;
	}

	return popped;
}


void         Heap::push(Star star, float score) {
	if (mCount == mCapacity) throw std::overflow_error("no space");

	mCount++;

	Entry newEntry;
	newEntry.star = star;
	newEntry.score = score;

	mData[mCount - 1] = newEntry;

	// Perc
	size_t i = mCount - 1;
	while (i != 0 && mData[i].score > mData[(i - 1) / 2].score) {
		Entry temp = mData[i];
		mData[i] = mData[(i - 1) / 2];
		mData[(i - 1) / 2] = temp;
		i = (i - 1) / 2;
	}

}


const Heap::Entry& Heap::top() const {
	if (mCount == 0) throw std::underflow_error("no items");
	return *mData;
}



// ================================================
// ====== RTree     ===============================
// ================================================

// ====== Nodes     ===============================
Bound::Bound() {
	for (size_t i = 0; i < 3; i++) {
		bounds[i][0] = 0;
		bounds[i][1] = 0;
	}

	parent = nullptr;
	children.reserve(1);
}

Bound::Bound(Bound* bound, Bound* par) {
	children.reserve(M + 1);

	bounds[0][0] = bound->bounds[0][0];
	bounds[0][1] = bound->bounds[0][1];

	bounds[1][0] = bound->bounds[1][0];
	bounds[1][1] = bound->bounds[1][1];

	bounds[2][0] = bound->bounds[2][0];
	bounds[2][1] = bound->bounds[2][1];

	parent = par;
	children.push_back(bound);
}

Root::Root(Star star, Bound* par) {
	stars.reserve(SS + 1);

	bounds[0][0] = star.x;
	bounds[0][1] = star.x;

	bounds[1][0] = star.y;
	bounds[1][1] = star.y;

	bounds[2][0] = star.z;
	bounds[2][1] = star.z;
	
	stars.push_back(star);

	parent = par;
	children.reserve(1);
}


float Bound::volChange(float x, float y, float z) const {
	float dx = (x < bounds[0][0]) * (bounds[0][0] - x) 
			 + (x > bounds[0][1]) * (x - bounds[0][1]);

	float dy = (y < bounds[1][0]) * (bounds[1][0] - y) 
			 + (y > bounds[1][1]) * (y - bounds[1][1]);

	float dz = (z < bounds[2][0]) * (bounds[2][0] - z) 
			 + (z > bounds[2][1]) * (z - bounds[2][1]);

	float xl = bounds[0][1] - bounds[0][0];
	float yl = bounds[1][1] - bounds[1][0];
	float zl = bounds[2][1] - bounds[2][0];

	return ((xl + dx) * (yl + dy) * (zl + dz)) - (xl * yl * zl);
}

float Bound::distChange(float x, float y, float z) const {
	float dx = (x < bounds[0][0]) * (bounds[0][0] - x) 
			 + (x > bounds[0][1]) * (x - bounds[0][1]);

	float dy = (y < bounds[1][0]) * (bounds[1][0] - y) 
			 + (y > bounds[1][1]) * (y - bounds[1][1]);

	float dz = (z < bounds[2][0]) * (bounds[2][0] - z) 
			 + (z > bounds[2][1]) * (z - bounds[2][1]);

	float xl = bounds[0][1] - bounds[0][0];
	float yl = bounds[1][1] - bounds[1][0];
	float zl = bounds[2][1] - bounds[2][0];

	float xp = (xl + dx);
	float yp = (yl + dy);
	float zp = (zl + dz);

	return (xp * xp + yp * yp + zp * zp) - (xl * xl + yl * yl + zl * zl);
}

Bound* Bound::search(float x, float y, float z) {
	// Finds min volume change bound and searches that bound
	float min = children[0]->distChange(x, y, z);
	if (min == 0) return (*children.begin())->search(x, y, z);
	
	size_t ind = 0;
	for (size_t i = 1; i < children.size(); i++) {
		float testNode = children[i]->distChange(x, y, z);
		if (testNode == 0) return children[i]->search(x, y, z);
		else if (testNode < min) {
			min = testNode;
			ind = i;
		}
	}
	
	return children[ind]->search(x, y, z);
}

Bound* Bound::addSearch(float x, float y, float z) {
	float min = children[0]->distChange(x, y, z);
	if (min == 0) return (*children.begin())->addSearch(x, y, z);

	size_t ind = 0;
	for (size_t i = 1; i < children.size(); i++) {
		float testNode = children[i]->distChange(x, y, z);
		if (testNode == 0) return children[i]->addSearch(x, y, z);
		else if (testNode < min) {
			min = testNode;
			ind = i;
		}
	}

	// If it gets here, it's not in the box so it must update
	updateBounds(x, y, z);
	return children[ind]->addSearch(x, y, z);
}

Bound* Root::search(float x, float y, float z) {
	return this;
}

Bound* Root::addSearch(float x, float y, float z) {
	updateBounds(x, y, z);
	return this;
}

float Bound::vol() const {
	return  (bounds[0][1] - bounds[0][0]) *
			(bounds[1][1] - bounds[1][0]) *
			(bounds[2][1] - bounds[2][0]);
}


float Bound::totalVol(Bound b2) const {
	float xLen =  ((bounds[0][1] > b2.bounds[0][1]) ? bounds[0][1] : b2.bounds[0][1])
				- ((bounds[0][0] < b2.bounds[0][0]) ? bounds[0][0] : b2.bounds[0][0]);

	float yLen =  ((bounds[1][1] > b2.bounds[1][1]) ? bounds[1][1] : b2.bounds[1][1])
				- ((bounds[1][0] < b2.bounds[1][0]) ? bounds[1][0] : b2.bounds[1][0]);

	float zLen =  ((bounds[2][1] > b2.bounds[2][1]) ? bounds[2][1] : b2.bounds[2][1])
				- ((bounds[2][0] < b2.bounds[2][0]) ? bounds[2][0] : b2.bounds[2][0]);

	return xLen * yLen * zLen;
}

void Root::defPush(Star star) {
	stars.push_back(star);
	updateBounds(star.x, star.y, star.z);
}

void Root::push(Star star) {
	stars.push_back(star);
	if (stars.size() > SS) split();
	else updateBounds(star.x, star.y, star.z);
}

void Bound::defAdd(Bound* bound) {
	children.push_back(bound);
	updateBounds(bound);
}

void Bound::addBound(Bound* bound) {
	children.push_back(bound);
	if (children.size() > M) split();
	else updateBounds(bound);
}

void Bound::split() {
	auto max1 = children.begin();
	auto max2 = children.begin();
	float maxWaste = 0;

	// Loops through bound pairs to find most wasted volume 
	for (auto it1 = children.begin(); it1 < children.end(); ++it1) {
		for (auto it2 = it1 + 1; it2 < children.end(); ++it2) {
			float testVol = (*it1)->totalVol(*it2) - (*it1)->vol() - (*it2)->vol();
			if (testVol > maxWaste) {
				maxWaste = testVol;
				max1 = it1;
				max2 = it2;
			}
		}
	}

	// Separates pair into 2 new bounds
	Bound* jBound = new Bound(*max2, parent);

	bounds[0][0] = (*max1)->bounds[0][0];
	bounds[0][1] = (*max1)->bounds[0][1];

	bounds[1][0] = (*max1)->bounds[1][0];
	bounds[1][1] = (*max1)->bounds[1][1];

	bounds[2][0] = (*max1)->bounds[2][0];
	bounds[2][1] = (*max1)->bounds[2][1];

	children.erase(max2);

	// Reallocates bounds into new parent bounds
	auto it = children.begin();
	while (it != children.end()) {
		if (totalVol(*it) > jBound->totalVol(*it)) {
			jBound->defAdd(*it);
			it = children.erase(it);
		}
		else {
			updateBounds(*it);
			it++;
		}
	}

	// Adds second bound to leaf
	if (parent) parent->addBound(jBound);
	else {
		parent = new Bound(this);
		parent->defAdd(jBound);
	}
}

void Bound::updateBounds(float x, float y, float z) {
	if (x > bounds[0][1]) bounds[0][1] = x;
	else bounds[0][0] = (x < bounds[0][0]) ? x : bounds[0][0];


	if (y > bounds[1][1]) bounds[1][1] = y;
	else bounds[1][0] = (y < bounds[1][0]) ? y : bounds[1][0];

	if (z > bounds[2][1]) bounds[2][1] = z;
	else bounds[2][0] = (z < bounds[2][0]) ? z : bounds[2][0];
}

void Bound::updateBounds(Bound b2) {
	for (size_t i = 0; i < 3; i++) {
		bounds[i][0] = (bounds[i][0] < b2.bounds[i][0]) ? bounds[i][0] : b2.bounds[i][0];
		bounds[i][1] = (bounds[i][1] > b2.bounds[i][1]) ? bounds[i][1] : b2.bounds[i][1];
	}
}


void Root::split() {

	size_t maxi = 0;
	size_t maxj = 0;
	float maxVol = 0;

	// Loops through stars to find furthest pair 
	for (size_t i = 0; i < stars.size(); i++) {
		for (size_t j = i + 1; j < stars.size(); j++) {
			float testVol =
			abs((stars[i].x - stars[j].x) * (stars[i].y - stars[j].y) * (stars[i].z - stars[j].z));
			if (testVol > maxVol) {
				maxVol = testVol;
				maxi = i;
				maxj = j;
			}
		}
	}

	// Separates pair into 2 new bounds
	Root* jRoot = new Root(stars[maxj], parent);

	bounds[0][0] = stars[maxi].x;
	bounds[0][1] = stars[maxi].x;

	bounds[1][0] = stars[maxi].y;
	bounds[1][1] = stars[maxi].y;

	bounds[2][0] = stars[maxi].z;
	bounds[2][1] = stars[maxi].z;

	stars.erase(stars.begin() + maxj);

	

	// Reallocates stars into new bounds
	auto it = stars.begin();
	while (it != stars.end()) {
		if (distChange(it->x, it->y, it->z) > jRoot->distChange(it->x, it->y, it->z)) {
			jRoot->defPush(*it);
			it = stars.erase(it);
		}
		else {
			updateBounds(it->x, it->y, it->z);
			it++;
		}
	}


	// Adds second bound to leaf
	if (parent) parent->addBound(jRoot);
	else {
		parent = new Bound(this);
		parent->defAdd(jRoot);
		jRoot->parent = parent;
	}
}

void Bound::shred() {
	for (auto it = children.begin(); it < children.end(); ++it) {
		(*it)->shred();
		delete* it;
	}
}

std::vector<Star>* Root::starList() {
	return &stars;
}

void Bound::print(size_t level) {
	for (size_t i = 0; i < 3; i++) {
		std::cout << level << ": (" << bounds[i][0] << ", " << bounds[i][1] << ") | ";
	}
	std::cout << this << "\n--------------------------\n";
	for (auto it = children.begin(); it < children.end(); ++it) {
		(*it)->print(level + 1);
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Root::print(size_t level) {
	for (size_t i = 0; i < 3; i++) {
		std::cout << level << ": (" << bounds[i][0] << ", " << bounds[i][1] << ") | ";
	}
	std::cout << this << "\nstars: ";
	for (auto it = stars.begin(); it < stars.end(); ++it) {
		std::cout << "(" << it->x << ", " << it->y << ", " << it->z << "), ";
	}
	std::cout << "\n";
}

Bound* Bound::top() {
	if (parent == nullptr) return this;
	
	return parent->top();
}

std::vector<std::vector<Star>*> Bound::extend() {
	std::vector<std::vector<Star>*> output;
	output.reserve(children.size() * SS * M);
	for (auto it = children.begin(); it < children.end(); ++it) {
		std::vector<std::vector<Star>*> temp = (*it)->extend();
		output.insert(output.end(), temp.begin(), temp.end());
	}

	return output;
}

std::vector<std::vector<Star>*> Root::extend()  {
	std::vector<std::vector<Star>*> output;
	output.reserve(1);
	output.push_back(&stars);
	return output;
}
// ====== RTree     ===============================

RTree::RTree() {
	head = nullptr;
}

RTree::RTree(Star star) {
	head = new Root(star);
}


RTree::RTree(RTree&& other) {
	head = other.head;
	other.head = nullptr;
}

RTree::~RTree() {
	
}

void RTree::insert(Star star) {
	Bound* region = head->addSearch(star.x, star.y, star.z);

	region->push(star);

	head = head->top();
	
}

std::vector<Star>* RTree::find(float x, float y, float z) {
	return head->search(x, y, z)->starList();
}

Bound* RTree::rootB(float x, float y, float z) {
	return head->search(x, y, z);
}

void RTree::print() {
	head->print(0);
}

void RTree::shred() {
	if (head == nullptr) return;

	head->shred();
	delete head;
}
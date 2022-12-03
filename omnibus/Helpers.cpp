#include "Helpers.h"

// Space to implement helper class member functions.
Mapper::Mapper() {
	names.reserve(MAXNAMES);
	mapping.reserve(MAXHASH);

}


Mapper::Mapper(Mapper&& other) {
	mapping = std::move(other.mapping);
}


void Mapper::add(std::string name) {
	if (mapping.find(name) == mapping.end()) {
		Station stat;
		stat.id = mapping.size();
		mapping[name] = stat;
		names.push_back(name);
	}
	else return;
}

void Mapper::insert(const std::string& name, const std::string& last, std::string line, int weight) {
	Station::Edge newEdge;

	newEdge.line = line;
	newEdge.connection = &mapping.find(last)->second;
	newEdge.weight = weight;

	auto namePos = mapping.find(name);

	if (namePos != mapping.end()) namePos->second.edges.push_back(newEdge);
	else {
		Station stat;
		stat.id = mapping.size();
		stat.edges.push_back(newEdge);
		namePos = mapping.insert({ name, stat }).first;
		names.push_back(name);
	}

	newEdge.connection = &namePos->second;
	mapping[last].edges.push_back(newEdge);
}

paired Mapper::find(std::string name) { return mapping.find(std::move(name)); }

std::string Mapper::find(size_t index) { return names[index]; }


// ================================================
// =========== HEAP ===============================
// ================================================


#include <stdexcept>
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



const Entry& Heap::lookup(size_t index) const {
	if (index >= mCount) throw std::out_of_range("index is out of range");
	return mData[index];
}


Entry  Heap::pop() {
	if (mCount == 0) throw std::underflow_error("no items");

	Entry popped = mData[0];

	mData[0] = mData[mCount - 1];
	mCount -= 1;

	// Perc
	size_t i = 0;
LOOP:
	if (2 * i + 1 < mCount && mData[i].weight > mData[2 * i + 1].weight) {
		if (2 * i + 2 < mCount && mData[2 * i + 1].weight > mData[2 * i + 2].weight) {
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
	else if (2 * i + 2 < mCount && mData[i].weight > mData[2 * i + 2].weight) {
		Entry temp = mData[i];
		mData[i] = mData[2 * i + 2];
		mData[2 * i + 2] = temp;
		i = 2 * i + 2;
		goto LOOP;
	}

	return popped;
}


Entry  Heap::pushpop(Station* station, int weight) {
	if (mCount == 0) throw std::underflow_error("no items");

	Entry popped = mData[0];

	Entry newEntry;
	newEntry.station = station;
	newEntry.weight = weight;

	mData[0] = newEntry;

	// Perc
	size_t i = 0;
LOOP:
	if (2 * i + 1 < mCount && mData[i].weight > mData[2 * i + 1].weight) {
		if (2 * i + 2 < mCount && mData[2 * i + 1].weight < mData[2 * i + 2].weight) {
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
	else if (2 * i + 2 < mCount && mData[i].weight > mData[2 * i + 2].weight) {
		Entry temp = mData[i];
		mData[i] = mData[2 * i + 2];
		mData[2 * i + 2] = temp;
		i = 2 * i + 2;
		goto LOOP;
	}

	return popped;
}


void         Heap::push(Station* station, int weight) {
	if (mCount == mCapacity) throw std::overflow_error("no space");

	mCount++;

	Entry newEntry;
	newEntry.station = station;
	newEntry.weight = weight;

	mData[mCount - 1] = newEntry;

	// Perc
	size_t i = mCount - 1;
	while (i != 0 && mData[i].weight < mData[(i - 1) / 2].weight) {
		Entry temp = mData[i];
		mData[i] = mData[(i - 1) / 2];
		mData[(i - 1) / 2] = temp;
		i = (i - 1) / 2;
	}

}


const Entry& Heap::top() const {
	if (mCount == 0) throw std::underflow_error("no items");
	return *mData;
}
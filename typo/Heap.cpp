#include "Heap.h"

// ====== Handling ================================

Heap::Heap(size_t capacity) {
	mData = new Entry[capacity];
	mCapacity = capacity;
	mCount = 0;
}

Heap::Heap(const Heap& other) {
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
	if      (2 * i + 1 < mCount && mData[i].score > mData[2 * i + 1].score) {
		if (2 * i + 2 < mCount && mData[2 * i + 1].score > mData[2 * i + 2].score) {
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
	else if (2 * i + 2 < mCount && mData[i].score > mData[2 * i + 1].score) {
		Entry temp = mData[i];
		mData[i] = mData[2 * i + 2];
		mData[2 * i + 2] = temp;
		i = 2 * i + 2;
		goto LOOP;
	}

	return popped;
}


Heap::Entry  Heap::pushpop(const std::string& value, float score) {
	if (mCount == 0) throw std::underflow_error("no items");

	Entry popped = mData[0];

	Entry newEntry;
	newEntry.value = value;
	newEntry.score = score;

	mData[0] = newEntry;

	// Perc
	size_t i = 0;
LOOP:
	if (2 * i + 1 < mCount && mData[i].score > mData[2 * i + 1].score) {
		if (2 * i + 2 < mCount && mData[2 * i + 1].score > mData[2 * i + 2].score) {
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
	else if (2 * i + 2 < mCount && mData[i].score > mData[2 * i + 1].score) {
		Entry temp = mData[i];
		mData[i] = mData[2 * i + 2];
		mData[2 * i + 2] = temp;
		i = 2 * i + 2;
		goto LOOP;
	}

	return popped;
}


void         Heap::push(const std::string& value, float score) {
	if (mCount == mCapacity) throw std::overflow_error("no space");
	
	mCount++;

	Entry newEntry;
	newEntry.value = value;
	newEntry.score = score;

	mData[mCount - 1] = newEntry;

	// Perc
	size_t i = mCount - 1;
	while (i != 0 && mData[i].score < mData[(i - 1) / 2].score) {
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
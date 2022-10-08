#include "FibVec.h"
#include <stdexcept>
#include <cstddef>


FibVec::FibVec() { // Default empty constucter
	vec = new int[1];
	num = 0;
}

FibVec::FibVec(int* arr, size_t arrSize) { // Construct with intial data
	size_t temp;
	num = arrSize;

	while (fib[1] < arrSize) {
		temp = fib[1];
		fib[1] += fib[0];
		fib[0] = temp;
	}

	vec = new int[fib[1]];
	for (size_t i = 0; i < arrSize; i++) { // Initialize data
		vec[i] = *(arr + i);
	}

}

FibVec::FibVec(const FibVec& fib1) {
	num = fib1.num;
	fib[0] = fib1.fib[0];
	fib[1] = fib1.fib[1];

	vec = new int[fib1.num];
	for (size_t i = 0; i < fib1.num; i++) vec[i] = fib1.vec[i];
}

const size_t FibVec::capacity() {
	return fib[1] * sizeof(*vec);
};

const size_t FibVec::count() {
	return num;
};

const int FibVec::lookup(size_t index) {
	if (index >= num) throw std::out_of_range("index is out of range");
	else return vec[index];
}

void FibVec::insert(int val, size_t index) {
	if (index >= num) throw std::out_of_range("index is out of range");
	else vec[index] = val;
}

void FibVec::upsize() {

	int* temp = vec;
	size_t fibTemp;

	fibTemp = fib[1];
	fib[1] += fib[0];
	fib[0] = fibTemp;

	vec = new int[fib[1]];

	for (size_t i = 0; i < fib[0]; i++) {
		vec[i] = *(temp + i);
	}

	delete[] temp;

}

void FibVec::push(int val) {
	if (num == fib[1]) {
		upsize();
	}

	vec[num] = val;
	num += 1;
}

void FibVec::downsize(size_t ignore) {
	int* temp = vec;
	size_t fibTemp;

	while (fib[1] - fib[0] > num - 1) {
		fibTemp = fib[1];
		fib[1] = fib[0];
		fib[0] = fibTemp - fib[0];
	}

	vec = new int[fib[1]];
	for (size_t i = 0; i < num; i++) {
		if (i < ignore) vec[i] = *(temp + i);
		else if (i != ignore) vec[i - 1] = *(temp + i);
	
	}

	delete[] temp;


}

int FibVec::remove(size_t index) {
	if (index >= num) throw std::out_of_range("index is out of range");

	int removed = vec[index];
	if (num <= fib[1] - fib[0]) downsize(index);
	else {
		for (size_t i = index; i < num - 1; i++) {
			vec[i] = vec[i + 1];
		}
	}

	num -= 1;
	return removed;
}

int FibVec::pop() {
	if (num == 0) throw std::underflow_error("index is out of range");

	int popped = vec[num - 1];

	if (num <= fib[1] - fib[0]) downsize(num - 1);

	num -= 1;
	return popped;
}

FibVec FibVec::slice(size_t index, size_t count) {
	size_t newSize;
	if (num > index) {
		newSize = count > num - index ? num - index : count;

	}
	else newSize = 0;

	FibVec sliced(vec + index, newSize);

	return sliced;
}

FibVec::~FibVec() {
	delete[] vec;
}
#include "FibVec.h"
#include <iostream>
#include <cstddef>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

void da(FibVec fibb) {
	std::cout << "{";
	for (size_t i = 0; i < fibb.count(); i++) std::cout << fibb.lookup(i) << ", ";
	std::cout << "}\n";
	std::cout << "Capacity: " << fibb.capacity() << ", Count: " << fibb.count() << "\n\n";

}

int main() {
	int arr[30];

	for (int i = 0; i < 30; i++) arr[i] = i;
	
	FibVec baby(arr, 30);
	FibVec p;

	da(baby);

	for (int i = 0; i < 30; i++) {
		baby.pop();
		da(baby);
	}




  return 0;
}

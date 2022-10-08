#include "FibVec.h"
#include <iostream>
#include <cstddef>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

const void da(FibVec fibb) {
	std::cout << "{";
	for (size_t i = 0; i < fibb.count(); i++) std::cout << fibb.lookup(i) << ", ";
	std::cout << "}\n";
	std::cout << "Capacity: " << fibb.capacity()/4 << ", Count: " << fibb.count() << "\n\n";

}

int main() {
	int arr[13] = {0, 1,2,3,4,5, 6, 7, 8, 9, 10, 11, 12}; // 1, 1, 2, 3, 5, 8, 13
	
	FibVec baby(arr, 13);

	da(baby);
	baby.push(69);
	da(baby);

	FibVec q = baby.slice(9, 2);

	da(q);

  return 0;
}

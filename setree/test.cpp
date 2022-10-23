#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
	std::string a = "aa";
	std::string	b = "bb";
	std::string c = "cc";
	std::string d = "dd";
	std::string e = "ee";
	std::string f = "ff";
	std::string g = "gg";
	std::string h = "hh";
	std::string	i = "ii";
	std::string j = "jj";
	std::string k = "kk";
	std::string l = "ll";
	std::string m = "mm";
	std::string n = "nn";

	Set set;

	std::cout << "count: " << set.count() << "\n";
	set.print();

	set.insert(d);
	set.insert(a);
	set.insert(c);
	set.insert(b);


	set.print();

	set.remove(g);

	std::cout << "count: " << set.count() << "\n";
	set.print();


	return 0;
}

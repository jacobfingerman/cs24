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

	set.insert(n);
	set.insert(a);
	set.insert(g);
	set.insert(f);
	set.insert(d);
	set.insert(e);
	set.insert(c);
	set.insert(b);
	set.insert(m);
	set.insert(k);
	set.insert(l);
	set.insert(i);
	set.insert(j);

	std::cout << "count: " << set.count() << "\n";
	set.print();


	set.remove(c);
	set.remove(i);

	std::cout << "count: " << set.count() << "\n";
	set.print();

	set.remove(f);
	set.remove(h);

	std::cout << "count: " << set.count() << "\n";
	set.print();

	set.remove(n);

	set.print();

	set.remove(a);

	std::cout << "count: " << set.count() << "\n";
	set.print();

	return 0;
}

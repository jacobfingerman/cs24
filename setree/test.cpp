#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
	std::string a = "aa";
	std::string	b = "bb";
	std::string c = "bc";
	std::string d = "dd";
	std::string e = "ee";
	std::string f = "ff";
	std::string g = "gg";

	std::string of = "cc";
	std::string oe = "dz";
	std::string ot = "dy";


	Set set;



	set.insert(a);
	set.insert(b);
	set.insert(c);
	set.insert(d);
	set.insert(e);
	set.insert(f);
	set.insert(g);

	set.print();
	std::cout << set.count() << "\n";

	set.insert(oe);
	set.print();

	Set q = set;

	q.print();

	set.print();


	set.remove(a);


	q.print();
	set.print();


/*
	set.print();

	std::cout << set.insert(c) << "\n";
	set.print();

	std::cout << set.insert(b) << "\n";

	std::cout << set.insert(b) << "\n";
	set.print();

	std::cout << set.insert(e) << "\n";
	set.print();

	std::cout << set.insert(a) << "\n";
	set.print();

	std::cout << set.contains(b) << "\n";

	std::cout << set.insert(a) << "\n";
	std::cout << set.insert(d) << "\n";
	std::cout << set.insert(f) << "\n";
	std::cout << set.insert(g) << "\n";
	set.print();

	std::cout << set.lookup(0) << "\n";
	std::cout << set.lookup(1) << "\n";
	std::cout << set.lookup(2) << "\n";
	std::cout << set.lookup(3) << "\n";
	std::cout << set.lookup(4) << "\n";
	std::cout << set.lookup(5) << "\n";
	std::cout << set.lookup(6) << "\n";

	set.remove("adadsasafgafsf");
	set.print();

	set.remove(a);
	set.print();

	set.remove(f);
	set.print();

	set.insert(of);
	set.insert(oe);
	set.insert(ot);
	set.print();

	set.remove(e);
	set.print();

	set.remove(c);
	set.print();




	std::cout << set.clear() << "\n";
	set.print();


*/
	return 0;
}

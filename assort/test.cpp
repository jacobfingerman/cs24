#include "List.h"
#include <iostream>

// Use this file to test your List class!
// This file won't be graded - do whatever you want.

int main() {
  List list;
  std::string a, b, c, d, e;

  a = "a woman";
  b = "be hot chip";
  c = "a man";

  list.insert(c);
  list.insert(b);
  list.insert(a);
  list.insert(b);
  list.insert(b);
  list.insert(b);
  list.insert(c);

  list.print();
  list.print(1);

  std::cout << "\n";

  std::cout << list.remove(a) << "\n";
  list.print();

  std::cout << list.remove(1) << "\n";
  list.print();

  std::cout << list.remove(0) << "\n";
  list.print();

  List q = list;
  q.print();

  return 0;
}

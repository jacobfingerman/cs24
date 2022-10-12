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
  list.insert(a);
  list.insert(b);
  list.insert(b);
  list.insert(c);

  list.print();

  std::cout << "\n";

  list.remove(4);
  list.print();

  return 0;
}

#include "Heap.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream>

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

void print(Heap* he) {
    for (size_t i = 0; i < he->count(); i++) {
        Heap::Entry q = he->lookup(i);
        std::cout << q.value << ": " << q.score << "\n";
    }
    std::cout << "\n";
}

int main(int argc, char** argv) {
    Heap heap(8);

    std::ifstream stream(argv[1]);

    Point b = {4.75, 2.00};
    Point e = { 2.00, 0.00 };

    std::vector<Point> zz;

    zz.push_back(b);
    zz.push_back(e);

    Dictionary l(stream);

    Heap q = l.correct(zz, 8, 0);

    print(&q);

    return 0;
}

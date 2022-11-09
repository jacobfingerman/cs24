#include "Heap.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

void print(Heap* he) {
    for (size_t i = 0; i < he->count(); i++) {
        Heap::Entry q = he->lookup(i);
        std::cout << q.value << ": " << q.score << "\n";
    }
    std::cout << "\n";
}

std::vector<Point> read_points(const std::string& line) {
    Point point;
    std::vector<Point> results;
    std::istringstream stream(line);
    while (stream >> point.x) {
        if (!(stream >> point.y)) {
            throw std::runtime_error("Odd number of points.");
        }

        results.push_back(point);
    }

    if (results.size() == 0) {
        throw std::runtime_error("No points given.");
    }

    return results;
}

int main() {

    std::string file = "data/top1000.txt";

    std::ifstream stream(file);

    std::vector<Point> zz = read_points(
        "2.600 0.940  6.919 0.657  2.599 1.450  4.220 0.209  6.901 0.323  8.011 0.220  5.784 2.112  0.087 0.847  3.010 -0.448  5.325 -0.166");

    Dictionary l(stream);



    Heap q = l.correct(zz, 3, 0);

    print(&q);

    return 0;
}

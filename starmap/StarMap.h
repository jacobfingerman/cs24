#ifndef STARMAP_H
#define STARMAP_H

#include "Star.h"

#include <istream>
#include <map>
#include<vector>
#include <string>

struct cmp {
    bool operator() (Star a, Star b) const {
        return a.x < a.y;
    }
};

class StarMap {
public:
    // Required Class Function
    static StarMap* create(std::istream& stream);

private:
    // Member Variables
    std::map<float, Star> map;
public:
    // Constructor & Destructor
    StarMap(std::istream& stream);
    ~StarMap();

    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);

    // Other Member Functions
};

#endif

#include "StarMap.h"
#include <iostream>

StarMap::StarMap(std::istream& stream) {
    std::string line;

    // RTree creation using first star
    std::getline(stream, line);
    size_t inds[2];
    inds[0] = line.find(9);
    inds[1] = line.find(9, inds[0] + 1);

    Star star;

    star.id = 1;
    star.x = stof(line.substr(0, inds[0]));
    star.y = stof(line.substr(inds[0], inds[1]));
    star.z = stof(line.substr(inds[1], line.size()));

    map = RTree(star);

    // Looping through the rest of stars
    size_t i = 2;
    while (std::getline(stream, line)) {
        
        size_t inds[2];
        inds[0] = line.find(9);
        inds[1] = line.find(9, inds[0] + 1);

        Star star;

        star.id = i;
        star.x = stof(line.substr(0, inds[0]));
        star.y = stof(line.substr(inds[0], inds[1]));
        star.z = stof(line.substr(inds[1], line.size()));

        map.insert(star);
        i++;
    }

}

StarMap::~StarMap() {
    map.shred();
}




StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}


std::vector<Star> StarMap::find(size_t n, float x, float y, float z) {

    Heap heap(n);

    Bound* cBound = map.rootB(x, y, z);
    std::vector<Star>* stars1 = cBound->starList();

    for (auto it = stars1->begin(); it < stars1->end(); ++it) {

        // Score calculation

        float dx = it->x - x;
        float dy = it->y - y;
        float dz = it->z - z;

        float score = dx * dx + dy * dy + dz * dz;

        // How to add to heap (if at all)

        if (heap.count() == heap.capacity()) {
            if (score > heap.top().score) continue;
            else heap.pushpop(*it, score);
        }
        else heap.push(*it, score);
    }

    cBound = cBound->par();

    while (heap.count() != n) {
        std::vector<std::vector<Star>*> stars2 = cBound->extend();

        for (auto vec = stars2.begin(); vec < stars2.end(); ++vec) {
            stars1 = *vec;
            for (auto it = stars1->begin(); it < stars1->end(); ++it) {

                // Score calculation

                float dx = it->x - x;
                float dy = it->y - y;
                float dz = it->z - z;

                float score = dx * dx + dy * dy + dz * dz;

                // How to add to heap (if at all)

                if (heap.count() == heap.capacity()) {
                    if (score > heap.top().score) continue;
                    else heap.pushpop(*it, score);
                }
                else heap.push(*it, score);
            }
        }
        cBound = cBound->par();

    }

    std::vector<std::vector<Star>*> stars2 = cBound->extend();

    for (auto vec = stars2.begin(); vec < stars2.end(); ++vec) {
        stars1 = *vec;
        for (auto it = stars1->begin(); it < stars1->end(); ++it) {

            // Score calculation

            float dx = it->x - x;
            float dy = it->y - y;
            float dz = it->z - z;

            float score = dx * dx + dy * dy + dz * dz;

            // How to add to heap (if at all)

            if (heap.count() == heap.capacity()) {
                if (score > heap.top().score) continue;
                else heap.pushpop(*it, score);
            }
            else heap.push(*it, score);
        }
    }

    std::vector<Star> output(n);

    for (size_t i = n; i > 0; i--) { output[i - 1] = heap.pop().star; }
  

    return output;
    
}
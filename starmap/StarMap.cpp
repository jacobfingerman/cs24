#include "StarMap.h"
#include "Helpers.h"

StarMap::StarMap(std::istream& stream) {
    std::string line;
    size_t i = 1;
    while (std::getline(stream, line)) {
        size_t inds[2];
        inds[0] = line.find(9);
        inds[1] = line.find(9, inds[0] + 1);

        Star star;

        star.id = i;
        star.x = stof(line.substr(0, inds[0]));
        star.y = stof(line.substr(inds[0], inds[1]));
        star.z = stof(line.substr(inds[1], line.size()));

        map.push_back(star);
        i++;
    }

}

StarMap::~StarMap() {

}




StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.


  return new StarMap(stream);
}


std::vector<Star> StarMap::find(size_t n, float x, float y, float z) {
    Heap heap(n);

    for (auto it = map.begin(); it < map.end(); ++it) {

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

    std::vector<Star> output(n);

    for (size_t i = n; i > 0; i--) { output[i - 1] = heap.pop().star; }
   
    return output;
}
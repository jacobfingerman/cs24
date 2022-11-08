#include "Dictionary.h"
#include <cmath>

Dictionary::Dictionary(std::istream& stream) {
    std::string line;
    while (getline(stream, line)) {
        bool word = true;
        for (size_t i = 0; i < line.length(); i++) {
            if (line[i] < 'a' || line[i] > 'z') {
                word = false;
                break;
            }
        }
        if (word && line != "") mWords.push_back(line);
    }
}

Heap Dictionary::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);

    for (auto it = mWords.begin(); it < mWords.end(); ++it) {
        if (it->length() != points.size()) continue;
        
        // Score calculation

        float score = 0;

        for (size_t i = 0; i < points.size(); i++) {
            Point lPoint = QWERTY[(*it)[i] - 'a'];
            float d = std::hypot(lPoint.x - points[i].x, lPoint.y - points[i].y);
            score += 1 / (10 * pow(d, 2) + 1);
        }

        score /= points.size();

        // How to add to heap (if at all)

        if (score < cutoff) continue;
        else if (heap.capacity() == heap.count()) {
            if (score < heap.top().score) continue;
            else heap.pushpop(*it, score);
        }
        else heap.push(*it, score);

    }

	return heap;
}
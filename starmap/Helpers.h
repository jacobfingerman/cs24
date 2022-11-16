#ifndef HELPERS_H
#define HELPERS_H

#include "Star.h"
#include <cstddef>

// If you want to add any helper classes,
// here's some space to do it in.


class Heap {
public:
    struct Entry {
        Star       star;
        float       score;
    };

private:
    Entry* mData;
    size_t mCapacity;
    size_t mCount;

public:
    Heap(size_t capacity);
    Heap(const Heap& other);
    Heap(Heap&& other);
    ~Heap();

    size_t       capacity() const;
    size_t       count() const;
    const Entry& lookup(size_t index) const;
    Entry        pop();
    Entry        pushpop(Star star, float score);
    void         push(Star star, float score);
    const Entry& top() const;
};

#endif

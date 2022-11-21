#ifndef HELPERS_H
#define HELPERS_H

#define M 5
#define SS 10

#include "Star.h"
#include <cstddef>
#include <vector>

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


// RTree


class Bound {
protected:
    Bound* parent;
    std::vector<Bound*> children;

public:
    float bounds[3][2];

    Bound();
    Bound(Bound* bound, Bound* par = nullptr);

    float volChange(float x, float y, float z) const;
    float distChange(float x, float y, float z) const;

    float vol() const;
    float totalVol(Bound b2) const;

    void updateBounds(float x, float y, float z);
    void updateBounds(Bound b2);

    virtual Bound* search(float x, float y, float z);
    virtual Bound* addSearch(float x, float y, float z);

    void split();

    void defAdd(Bound* bound);
    void addBound(Bound* bound);

    virtual void push(Star star) {}
    virtual std::vector<Star>* starList() { return nullptr;}
    void shred();
    virtual void print(size_t level);
    Bound* top();
    Bound* par() { return parent; }
    virtual std::vector<std::vector<Star>*> extend();
};


class Root : public Bound {

    std::vector<Star> stars;

public:
    Root(Star star, Bound* par = nullptr);

    Bound* search(float x, float y, float z);
    Bound* addSearch(float x, float y, float z);

    void Root::defPush(Star star);

    void split();

    void push(Star star);
    std::vector<Star>* starList();
    void print(size_t level);
    std::vector<std::vector<Star>*> extend();

};

class RTree {
    Bound* head;
    
public:
    RTree();
    RTree(Star star);
    RTree(const RTree& other) = default;
    RTree& operator=(const RTree&) = default;
    RTree(RTree&& other);
    ~RTree();

    void insert(Star star);
    std::vector<Star>* find(float x, float y, float z);
    void print();
    void shred();

    Bound* rootB(float x, float y, float z);
};


#endif
#ifndef HELPERS_H
#define HELPERS_H

#define MAXNAMES 40000
#define MAXHASH 80000
#define MAXINT 2147483647

#define paired std::unordered_map<std::string, Station>::iterator

// ================================================
// =========== MAPPER =============================
// ================================================

#include<string>
#include<vector>
#include<unordered_map>
#include <stdexcept>

// If you want to add any helper classes,
// here's some space to do it in.

struct Station {
	struct Edge {
		std::string line;
		Station* connection;
		int weight;
	};

	std::vector<Edge> edges;
    size_t id;

    Station() {
        edges.reserve(512);
        id = -1;
    }


};

class Mapper {
	std::unordered_map<std::string, Station> mapping;
    std::vector<std::string> names;
public:
	Mapper();
	Mapper(Mapper&& other);
	Mapper& operator=(const Mapper&) = default;

	size_t size() const { return mapping.size(); }
    paired end() { return mapping.end(); }

	void add(std::string name);
	void insert(const std::string& name, const std::string& last, std::string line, int weight);
	paired find(std::string name);
    std::string find(size_t index);
};

struct Entry {
	Station* station;
    int weight;

    Entry(Station* _station, int _weight) {
        station = _station;
        weight = _weight;
    }
    Entry() {
        station = nullptr;
        weight = MAXINT;
    }
};

// ================================================
// =========== HEAP ===============================
// ================================================


class Heap {
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
    Entry        pushpop(Station* station, int weight);
    void         push(Station* station, int weight);
    const Entry& top() const;
};

#endif

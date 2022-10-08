#include <cstddef>

class FibVec {
private:
	int* vec = nullptr;
	size_t num;
	size_t fib[2] = {1, 1}; //f_n, f_n-1

	void upsize();
	void downsize(size_t ignore);

public:
	FibVec();
	FibVec(int* arr, size_t arrSize);

	FibVec(const FibVec& fib1);

	const size_t capacity();
	const size_t count();
	void insert(int val, size_t index);
	const int lookup(size_t index);
	void push(int val);
	int remove(size_t index);
	int pop();
	FibVec slice(size_t index, size_t count);

	~FibVec();
};

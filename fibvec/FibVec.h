#include <cstddef>

class FibVec {
private:
	int* vec = nullptr;
	size_t num;
	size_t fib[2] = {1, 1}; //f_n, f_n-1
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 

	void upsize(int val, size_t index);
	void downsize(size_t ignore);

public:
	FibVec();
	FibVec(int* arr, size_t arrSize);

	FibVec(const FibVec& fib1);

	size_t capacity() const;
	size_t count() const;
	void insert(int val, size_t index);
	int lookup(size_t index) const;
	void push(int val);
	int remove(size_t index);
	int pop();
	FibVec slice(size_t index, size_t count);

	~FibVec();
};

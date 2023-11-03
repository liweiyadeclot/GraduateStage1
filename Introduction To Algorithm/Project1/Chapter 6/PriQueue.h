#pragma once
#include <vector>
#include "MaxHeap.h"

template <typename T>
class PriQueue
{
public:
	PriQueue() = default;
	PriQueue(std::vector<T>& source);
	~PriQueue() = default;

	void Insert(T x);
	T Maximum();
	T ExtractMax();
	void IncreaseKey(T x, int index, T k);
private:
	MaxHeap<T> A;
};



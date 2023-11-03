#pragma once
#include <iostream>
#include <vector>

template <typename T>
class MaxHeap
{
public:
	MaxHeap() = default;
	MaxHeap(std::vector<T>& source);
	~MaxHeap() = default;

	int Parent(int i);
	void MaxHeapify(int i);
	void IncreaseHeapsize();
	void DecreaseHeapsize();
	int GetHeapsize();
public:
private:
	int Left(int i);
	int Right(int i);

private:
	int heapsize;
	std::vector<T> A;
};
#pragma once
#include <vector>
#include <iostream>
#include "Heap.h"

// class Minheap and class Maxheap should derived from
// the conmmon base class Heap, which gives implementation
// of functions like Parent(), Left(), right()
namespace Chapter6
{
	template <typename T>
	class MinHeap : public Heap<T>
	{
	public:
		MinHeap() = delete;
		MinHeap(std::vector<T>& source);
		~MinHeap() = default;

		void MinHeapify(int i);

	};

	template<typename T>
	inline MinHeap<T>::MinHeap(std::vector<T>& source)
		: Heap<T>(source)
	{
		for (int i = Heap<T>::heapsize / 2; i >= 0; --i)
		{
			MinHeapify(i);
		}
	}

	template<typename T>
	inline void MinHeap<T>::MinHeapify(int i)
	{
		int l = Heap<T>::Left(i);
		int r = Heap<T>::Right(i);
		int smallest;
		if (l != -1 && l <= Heap<T>::heapsize && 
			Heap<T>::A[l] < Heap<T>::A[i])
		{
			smallest = l;
		}
		else
		{
			smallest = i;
		}
		if (r != -1 && r <= Heap<T>::heapsize && 
			Heap<T>::A[r] < Heap<T>::A[smallest])
		{
			smallest = r;
		}
		if (smallest != i)
		{
			std::swap(Heap<T>::A[i], Heap<T>::A[smallest]);
			MinHeapify(smallest);
		}
	}

}

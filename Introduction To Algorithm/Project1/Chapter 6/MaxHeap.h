#pragma once
#include <iostream>
#include <vector>
#include "Heap.h"

namespace Chapter6
{
	template <typename T>
	class MaxHeap : public Heap<T>
	{
	public:
		MaxHeap() = default;
		MaxHeap(std::vector<T> source);
		~MaxHeap() = default;

		void MaxHeapify(int i);

	};

	template <typename T>
	MaxHeap<T>::MaxHeap(std::vector<T> source) :
		Heap<T>(source)
	{
		for (int i = Heap<T>::heapsize / 2; i > 0; --i)
		{
			MaxHeapify(i);
		}
	}

	template <typename T>
	void MaxHeap<T>::MaxHeapify(int i)
	{
		int l = Heap<T>::Left(i);
		int r = Heap<T>::Right(i);
		int largest;
		if (l != -1 && l <= Heap<T>::heapsize && 
			Heap<T>::A[l] > Heap<T>::A[i])
		{
			largest = l;
		}
		else
		{
			largest = i;
		}
		if (r != -1 && r <= Heap<T>::heapsize &&
			Heap<T>::A[r] > Heap<T>::A[largest])
		{
			largest = r;
		}
		if (largest != i)
		{
			std::swap(Heap<T>::A[i], Heap<T>::A[largest]);
			MaxHeapify(largest);
		}

	}


}

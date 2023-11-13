#pragma once
#include <vector>
#include "MaxHeap.h"

namespace Chapter6
{
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

		void print();
	private:
		MaxHeap<T> A;
	};


	template <typename T>
	PriQueue<T>::PriQueue(std::vector<T>& source)
		: A(source) {}

	template<typename T>
	void PriQueue<T>::Insert(T x)
	{
		A.IncreaseHeapsize();

		int i = A.GetHeapsize();

		A[i] = x;

		while (i > 0 && A[A.Parent(i)] < A[i])
		{
			std::swap(A[i], A[A.Parent(i)]);
			i = Parent(i);
		}
	}

	template<typename T>
	T PriQueue<T>::Maximum()
	{
		return A[1];
	}

	template<typename T>
	T PriQueue<T>::ExtractMax()
	{
		if (A.GetHeapsize() < 1)
		{
			std::cout << "error! heap underflow" << std::endl;
			return T();
		}
		T max = A[1];
		A[1] = A[A.GetHeapsize()];
		A.DecreaseHeapsize();
		A.MaxHeapify(1);
		return max;
	}

	template<typename T>
	void PriQueue<T>::IncreaseKey(T x, int index, T k)
	{
		if (k < A[index])
		{
			std::cout << "new key is smaller than current key." << std::endl;
			return;
		}
		A[index] = k;
		while (index > 1 && A[A.Parent(index)] < A[index])
		{
			std::swap(A[index], A[A.Parent(index)]);
			index = A.Parent(index);
		}

	}

	template<typename T>
	void PriQueue<T>::print()
	{
		// do nothing
		return;
	}

}

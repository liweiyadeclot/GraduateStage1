#pragma once
#include <vector>
#include <iostream>

// Base class of MaxHeap and MinHeap
namespace Chapter6
{
	template <typename T>
	class Heap
	{
	public:
		Heap() = delete;
		Heap(std::vector<T> source) :
			A(source), heapsize(source.size())
		{
			A.insert(A.begin(), -1);
		}
		~Heap() = default;

		int Parent(int i);
		void IncreaseHeapsize();
		void DecreaseHeapsize();
		int GetHeapsize();
		void PrintElems();

		T& operator[](int index);

	protected:
		int Left(int i);
		int Right(int i);



		std::vector<T> A;
		int heapsize;
	};
	template<typename T>
	inline int Heap<T>::Parent(int i)
	{
		return i >> 1;
	}

	template<typename T>
	inline T& Heap<T>::operator[](int index)
	{
		return A[index];
	}

	template<typename T>
	inline int Heap<T>::Left(int i)
	{
		int res = i << 1;
		if (res <= heapsize)
			return res;
		else
			return -1;
	}

	template<typename T>
	inline int Heap<T>::Right(int i)
	{
		int res = (i << 1) + 1;
		if (res <= heapsize)
			return res;
		else
			return -1;
	}

	template<typename T>
	inline void Heap<T>::IncreaseHeapsize()
	{
		heapsize++;
		A.resize(heapsize + 1);
	}

	template<typename T>
	inline void Heap<T>::DecreaseHeapsize()
	{
		heapsize--;
		A.resize(heapsize + 1);
	}

	template<typename T>
	inline int Heap<T>::GetHeapsize()
	{
		return heapsize;
	}

	template<typename T>
	inline void Heap<T>::PrintElems()
	{
		for (size_t i = 1; i <= heapsize; ++i)
		{
			std::cout << A[i] << ", ";
		}
		std::cout << std::endl;
		return;
	}


}

#include "PriQueue.h"
#include <iostream>

template <typename T>
PriQueue<T>::PriQueue(std::vector<T>& source)
	: A(source){}

template<typename T>
void PriQueue<T>::Insert(T x)
{
	A.IncreaseHeapsize();

	int i = A.GetHeapsize();

	// heapsize = index + 1
	i--;
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
	return A[0];
}

template<typename T>
T PriQueue<T>::ExtractMax()
{
	if (A.GetHeapsize() < 1)]
	{
		std::cout << "error! heap underflow" << std::endl;
		return T();
	}
	T max = A[0];
	A.DecreaseHeapsize();
	A.MaxHeapify(0);
	return max;
}

template<typename T>
void PriQueue<T>::IncreaseKey(T x, int index, T k)
{
	if (key < A[index])
	{
		std::cout << "new key is smaller than current key." << std::endl;
		return;
	}
	A[index] = k;
	while (index > 0 && A[A.Parent(index)] < A[index])
	{
		std::swap(A[index], A[A.Parent(index)]);
		i = A.Parent(index);
	}

}

#include "MaxHeap.h"

template <typename T>
MaxHeap<T>::MaxHeap(std::vector<T>& source) : 
	A(source), heapsize(source.size())
{
	for (size_t i = A.size() / 2; i >= 0; --i)
	{
		MaxHeapify(i);
	}
}

template <typename T>
int MaxHeap<T>::Parent(int i)
{
	return i >> 1;
}

template <typename T>
int MaxHeap<T>::Left(int i)
{
	int res = i << 1;
	if (res < heapsize - 1)
		return i << 1;
	else
		return -1;
}

template <typename T>
int MaxHeap<T>::Right(int i)
{
	int res = (i << 1) + 1;
	if (res < heapsize - 1)
		return i << 1;
	else
		return -1;
}

template <typename T>
void MaxHeap<T>::MaxHeapify(int i)
{
	int l = Left(i);
	int r = Right(i);
	int largest;
	if (l != -1 && l <= heapsize && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if (r != -1 && r <= heapsize && A[r] > A[i])
	{
		largest = r;
	}
	if (largest != i)
	{
		std::swap(A[i], A[largest]);
		MaxHeap(largest);
	}

}

template<typename T>
void MaxHeap<T>::IncreaseHeapsize()
{
	heapsize++;
	A.resize(heapsize);
}

template<typename T>
void MaxHeap<T>::DecreaseHeapsize()
{
	heapsize--;
	A.resize(heapsize);
}

template<typename T>
int MaxHeap<T>::GetHeapsize()
{
	return heapsize;
}

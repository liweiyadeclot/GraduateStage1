#pragma once
#include <iostream>
#include <vector>

namespace Chapter7
{
	int Partition(std::vector<int>& A, int p, int r)
	{
		int x = A[r];
		int i = p - 1;
		for (int j = p; j <= r; ++j)
		{ 
			if (A[j] < x)
			{
				i++;
				std::swap(A[i], A[j]);
			}
		}

		std::swap(A[i + 1], A[r]);
		return i + 1;
	}

	void QuickSort(std::vector<int>& A, int p, int r)
	{
		if (p < r)
		{
			int q = Partition(A, 0, r);
			QuickSort(A, 0, q - 1);
			QuickSort(A, q + 1, r);
		}
		
	}
}
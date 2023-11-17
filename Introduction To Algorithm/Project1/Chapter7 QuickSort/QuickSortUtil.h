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

	int HoarePartition(std::vector<int>& A, int p, int r)
	{
		int x = A[p];
		int i = p - 1;
		int j = r + 1;
		while (true)
		{
			do
				j--;
			while (A[j] > x);

			do
				i++;
			while (A[i] < x);

			if (i < j)
				std::swap(A[i], A[j]);
			else
				return j;
		}

	}

	void HoareQuickSort(std::vector<int>&A, int p, int r)
	{
		if (p < r)
		{
			int q = HoarePartition(A, p, r);
			HoareQuickSort(A, p, q);
			HoareQuickSort(A, q + 1, r);
		}
		return;
	}

	void PartitionWithEqualElem(std::vector<int>& A, int p, int r)
	{
		int x = A[p];
		int low = p;
		int high = p;
		for (int j = p + 1; j <= r; ++j)
		{
			if (A[j] == x)
			{
				std::swap(A[high + 1], A[j]);
				high++;
			}
			else if (A[j] < x)
			{
				A[high]
			}
		}
	}

	void TailRecursiveQuickSort(std::vector<int>& A, int p, int r)
	{
		while (p < r)
		{
			// Partition and sort left subarray
			int q = Partition(A, p, r);
			TailRecursiveQuickSort(A, p, q - 1);
			p = q + 1;
		}
	}

	void TRQWithBetterStackDeepth(std::vector<int>& A, int p, int r)
	{

	}
}
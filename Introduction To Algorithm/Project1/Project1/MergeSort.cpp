#include <iostream>
#include <vector>
#include <limits>

void Merge(std::vector<int>& A, int p, int q, int r) 
{
	// L: [p, q], R: [q + 1, r]
	int leftLen = q - p + 1;
	int rightLen = r - q;

	std::vector<int> L(A.begin() + p, A.begin() + q);
	std::vector<int> R(A.begin() + q + 1, A.begin() + r);

	L.push_back(std::numeric_limits<int>::max());
	R.push_back(std::numeric_limits<int>::max());

	int i = 0;
	int j = 0;

	for (int k = 0; k <= r; ++k)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}

}

void MergeSort(std::vector<int>& A, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}
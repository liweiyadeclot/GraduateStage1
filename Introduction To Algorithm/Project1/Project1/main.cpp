#include "MergeSort.h"
#include "ArrayUtil.h"

int main(void)
{
	std::vector<int> A{ 3, 4, 2, 1, 44, 3, 32, 45, 67, 12};

	Chapter2::MergeSort(A, 0, A.size() - 1);
	Chapter2::OutputArray(A);

	return 0;
}
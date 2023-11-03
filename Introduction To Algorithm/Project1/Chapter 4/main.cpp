#include "MaxSubArray.h"

int main(void)
{
	std::vector<int> A{ 13, -3, -25, 20, -3, -16
						- 23, 18, 20, -7, 12,
						-5, -22, 15, -4, 7 };
	using namespace Chapter4;
	SubArrayInfo res = FindMaxSubarray(A, 0, A.size() - 1);
	std::cout << res.arraySum;
	return 0;
}
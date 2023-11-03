#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

namespace Chapter4
{
	struct SubArrayInfo
	{
		int leftIndex;
		int rightIndex;
		int arraySum;

		SubArrayInfo(int left, int right, int sum) :
			leftIndex(left), rightIndex(right), arraySum(sum){}

		bool operator<(const SubArrayInfo& rhs)
		{
			return arraySum < rhs.arraySum;
		}
	};

	SubArrayInfo FindMaxCrossingSubarray(const std::vector<int>& A,
		int low, int mid, int high)
	{
		int leftSum = std::numeric_limits<int>::min();
		int sum = 0;
		int maxLeftIndex;
		for (int i = mid; i >= low; --i)
		{
			sum += A[i];
			if (sum > leftSum)
			{
				leftSum = sum;
				maxLeftIndex = i;
			}
		}

		int rightSum = std::numeric_limits<int>::min();
		sum = 0;
		int maxRightIndex;

		for (int i = mid + 1; i <= high; ++i)
		{
			sum += A[i];
			if (sum > rightSum)
			{
				rightSum = sum;
				maxRightIndex = i;
			}
		}

		return SubArrayInfo(maxLeftIndex, maxRightIndex, leftSum + rightSum);
	}

	SubArrayInfo FindMaxSubarray(const std::vector<int>& A, int low, int high)
	{
		if (high == low)
		{
			return SubArrayInfo(low, high, A[low]);
		}
		else
		{
			int mid = (low + high) / 2;
			SubArrayInfo leftMaxSubArray = FindMaxSubarray(A, low, mid);
			SubArrayInfo rightMaxSubArray = FindMaxSubarray(A, mid + 1, high);
			SubArrayInfo crossMaxSubArray = FindMaxCrossingSubarray(A, low, mid, high);

			std::vector<SubArrayInfo> subArrays;
			subArrays.push_back(leftMaxSubArray);
			subArrays.push_back(rightMaxSubArray);
			subArrays.push_back(crossMaxSubArray);

			std::sort(subArrays.begin(), subArrays.end());

			return subArrays[subArrays.size() - 1];
		}
	}
}
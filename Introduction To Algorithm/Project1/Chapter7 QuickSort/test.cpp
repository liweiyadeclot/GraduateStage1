#include <iostream>
#include <vector>
#include "QuickSortUtil.h"
#include "VectorUtils.h"


using namespace std;

int main(void)
{
	vector<int> A{ 9, 12, 3, 0, 5 };
	//vector<int> A{ 5, 0, 3 };

	Chapter7::HoareQuickSort(A, 0, A.size() - 1);
	VectorUtils::PrintElems(A);
	return 0;
	
}

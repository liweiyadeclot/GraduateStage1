#include <iostream>
#include <vector>
#include "PriQueue.h"
#include "MinHeap.h"

using namespace Chapter6;

int main(void)
{
	//std::vector<int> source{ 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	std::vector<int> source{ 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	//PriQueue<int> A(source);
	MinHeap<int> B(source);
	B.PrintElems();
	//for (size_t i = 0; i < source.size(); i++)
	//{
	//	std::cout << A.ExtractMax() << std::endl;
	//}
	return 0;
}
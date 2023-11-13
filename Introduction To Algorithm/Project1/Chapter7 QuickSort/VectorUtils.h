#pragma once
#include <vector>
#include <iostream>

namespace VectorUtils
{
	template<typename T>
	void PrintElems(const std::vector<T>& A)
	{
		for (const auto& e : A)
		{
			std::cout << e << ", ";
		}
		std::cout << std::endl;
	}
}
#pragma once
#include <vector>
#include <iostream>

namespace Chapter2
{
	void OutputArray(const std::vector<int>& A)
	{
		for (const auto& a : A)
		{
			std::cout << a << ", ";
		}
		std::cout << std::endl;
		return;
	}
}
#pragma once
#include <iostream>

struct Node
{
	int i;
	Node* next;

	Node(int val) : i(val){}
};
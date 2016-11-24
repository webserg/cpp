#pragma once
#include <list>
using namespace std;
template<typename T>  class queue
{
	list<T> elems;
public:
	void push(T e)
	{
		elems.push_back(e);
	}
	int pop()
	{
		auto t = elems.front();
		elems.pop_front();
		return t;
	}
	bool empty() const
	{
		return elems.empty();
	}
};
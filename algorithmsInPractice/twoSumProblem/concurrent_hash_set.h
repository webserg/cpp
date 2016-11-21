#pragma once
#include <vector>
#include "thread_guard.h"
#include <mutex>
using namespace std;
class concurrent_hash_set
{
	vector<vector<int>> elems;
	int N;
	float load_factor = 0.75;
	int size;
	int getIdx(int);
	mutex mutex_guard;
public:
	vector<int> iter;
	explicit concurrent_hash_set(int n) :N(n)
	{
		size = N * load_factor;
		elems.reserve(size);
		iter.reserve(N);
		vector<int> empty;
		for (int i = 0; i < size; ++i)
		{
			elems.push_back(empty);
		}
	};

	void insert(int);
	int contains(int);

};

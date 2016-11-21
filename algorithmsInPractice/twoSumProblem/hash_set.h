#pragma once
#include <vector>
using namespace std;
class hash_set
{
	vector<vector<long long>> elems;
	int N;
	float load_factor = 0.75;
	int size;
	int getIdx(long long) const;
public:
	vector<long long> iter;
	explicit hash_set(int n) :N(n)
	{
		size = N * load_factor;
		elems.reserve(size);
		iter.reserve(N);
		vector<long long> empty;
		for (auto i = 0; i < size; ++i)
		{
			elems.push_back(empty);
		}
	};

	void insert(long long);
	int contains(long long);

};

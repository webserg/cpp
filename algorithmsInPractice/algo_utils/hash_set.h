#pragma once
#include <vector>
using namespace std;
template<typename T> class hash_set
{
	vector<vector<T>> elems;
	int N;
	float load_factor = 0.75;
	int size;
	int getIdx(T) const;
public:
	vector<T> iter;
	explicit hash_set(int n) :N(n)
	{
		size = N * load_factor;
		elems.reserve(size);
		iter.reserve(N);
		vector<T> empty;
		for (auto i = 0; i < size; ++i)
		{
			elems.push_back(empty);
		}
	};

	void insert(T);
	int contains(T);

};


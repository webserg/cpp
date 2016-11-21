#include "hash_set.h"
using namespace std;
int hash_set::getIdx(long long d) const
{
	int h = hash<long long>()(d);
	return h % elems.size();
}

void hash_set::insert(long long d)
{
	iter.push_back(d);
	elems[getIdx(d)].push_back(d);
}

int hash_set::contains(long long d)
{
	for (auto e : elems[getIdx(d)])
	{
		if (e == d) return 1;
	}
	return 0;
}

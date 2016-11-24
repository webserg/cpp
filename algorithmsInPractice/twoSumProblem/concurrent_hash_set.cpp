#include "concurrent_hash_set.h"

int concurrent_hash_set::getIdx(int d) const
{
	int h = hash<int>()(d);
	return h % elems.size();
}

void concurrent_hash_set::insert(int d)
{
	lock_guard<mutex> guard(mutex_guard);
	iter.push_back(d);
	elems[getIdx(d)].push_back(d);
}

int concurrent_hash_set::contains(int d)
{
	lock_guard<mutex> guard(mutex_guard);
	for (auto e : elems[getIdx(d)])
	{
		if (e == d) return 1;
	}
	return 0;
}

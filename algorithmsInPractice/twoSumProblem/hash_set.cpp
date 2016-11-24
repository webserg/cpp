#include "hash_set.h"
using namespace std;
template class hash_set <long long>;
template<typename T> int hash_set<T> ::getIdx(T d) const
{
	int h = hash<long long>()(d);
	return h % elems.size();
}

template<typename T> void hash_set<T>::insert(T d)
{
	iter.push_back(d);
	elems[getIdx(d)].push_back(d);
}

template<typename T> int hash_set<T>::contains(T d)
{
	for (auto e : elems[getIdx(d)])
	{
		if (e == d) return 1;
	}
	return 0;
}

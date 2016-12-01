#pragma once
#include <iosfwd>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

inline void merge(vector<int>::iterator iter, int first, int mid, int last)
{
	vector<int> temp(last - first + 1);
	int l = first;
	int r = mid;
	int i = 0;
	for (; l < mid && r <= last; i++) {
		if (iter[l] < iter[r]) {
			temp[i] = iter[l++];
		}
		else {
			temp[i] = iter[r++];
		}
	}
	while (l < mid) temp[i++] = iter[l++];
	while (r <= last) temp[i++] = iter[r++];
	for (auto k = 0, s = first; k < last - first + 1; k++, s++)
	{
		iter[s] = temp[k];
	}
}


inline void split(vector<int>::iterator iter, int first, int last)
{
	if (first < last) {
		auto mid = (first + last) >> 1;
		split(iter, first, mid);
		split(iter, mid + 1, last);
		merge(iter, first, mid + 1, last);
	}
}

inline void mergeSort(vector<int>::iterator start, vector<int>::iterator end)
{
	split(start, 0, end - start - 1);
}

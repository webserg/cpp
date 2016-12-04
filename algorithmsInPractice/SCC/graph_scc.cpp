#include "graph_scc.h"
#include <algorithm>
#include "../mergeSort/mergeSort.h"
#include <cassert>

void graph_scc::merge(vector<int>::iterator iter, int first, int mid, int last)
{
	vector<int> temp(last - first + 1);
	auto l = first;
	auto r = mid;
	auto i = 0;
	for (; l < mid && r <= last; i++) {
		if (finish[iter[l]] > finish[iter[r]]) {
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


void graph_scc::split(vector<int>::iterator iter, int first, int last)
{
	if (first < last) {
		auto mid = (first + last) >> 1;
		split(iter, first, mid);
		split(iter, mid + 1, last);
		merge(iter, first, mid + 1, last);
	}
}

void graph_scc::mergeSort(vector<int>::iterator start, vector<int>::iterator end)
{
	split(start, 0, end - start - 1);
}


void graph_scc::dfs_visit(const int u)
{
	time++;
	colors[u] = GRAY;
	for (auto v : adjListOfV[u])
	{
		if (colors[v] == WHITE)
		{
			dfs_visit(v);
		}
	}
	colors[u] = BLACK;
	time++;
	finish[u] = time;
}


void graph_scc::dfs_visit_scc(const int u)
{
	colors[u] = GRAY;
	for (auto v : adjListOfV_T[u])
	{
		if (colors[v] == WHITE)
		{
			k++;
			dfs_visit_scc(v);
		}
	}
	colors[u] = BLACK;
}


void graph_scc::dfs()
{
	for (auto u = 0; u < adjListOfV.size(); u++)
	{
		if (colors[u] == WHITE)
		{
			dfs_visit(u);
		}
	}
}


void graph_scc::dfs_scc()
{
	for (auto i = 0; i < colors.size(); i++)
	{
		colors[i] = WHITE;
	}
	vector<int> sorted(adjListOfV_T.size() - 1);
	for (auto i = 0; i < adjListOfV_T.size() - 1; i++)
	{
		sorted[i] = i + 1;
	}
	mergeSort(sorted.begin(), sorted.end());
	for (auto u : sorted)
	{
		if (colors[u] == WHITE)
		{
			k = 1;
			dfs_visit_scc(u);
			size_scc_components.push_back(k);
			k = 0;

		}
	}
}

void graph_scc::printColors()
{
	for (auto i = 1; i < colors.size(); i++)
	{
		string col = colors[i] == BLACK ? "black" : colors[i] == WHITE ? "white" : "gray";
		cout << i << " " << col << "\n";
	}
}

void graph_scc::printLeaders()
{
	std::sort(size_scc_components.begin(), size_scc_components.end(), [](int a, int b) {return (a > b); });
	for (auto v : size_scc_components)
	{
		cout << v << " ";
	}
	cout << nl;
}

void graph_scc::comparesizeSCC(vector<int> vec) const
{
	assert((vec == size_scc_components),vec);
}

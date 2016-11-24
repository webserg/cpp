#pragma once
#include <vector>
#include <iostream>
#include<set>

/**
* Created by webse on 11/3/2016.
* <p>
* L ← Empty list that will contain the sorted elements
* S ← Set of all nodes with no incoming edges
* while S is non-empty do
* remove a node n from S
* add n to tail of L
* for each node m with an edge e from n to m do
* remove edge e from the graph
* if m has no other incoming edges then
* insert m into S
* if graph has edges then
* return error (graph has at least one cycle)
* else
* return L (a topologically sorted order)
*/

/*
4 4
1 2
1 3
2 4
3 4
std::ios::sync_with_stdio(false);
*/

using namespace std;

inline void least_lexicographic_topological_sort(const int N, const int M, bool test)
{
	vector<vector<int>> adjList(N + 1);
	vector<int> indegree(N + 1, 0);
	vector<int> order;
	set<int> minHeap;

	int x = 0, y = 0;
	for (int i = 0; i < M; i++)
	{
		scanf_s("%d", &x);
		scanf_s("%d", &y);
		adjList[x].push_back(y);
		indegree[y]++;
	}
	if (test == true)
	{
		for (auto i = 0; i < adjList.size(); i++)
		{
			cout << i << " -->";
			for (auto j = 0; j < adjList[i].size(); j++)
			{
				cout << adjList[i][j] << ",";
			}
			cout << endl;
		}
		for (auto i = 1; i <= N; i++)
		{
			cout << indegree[i] << endl;
		}
		cout << endl;
	}
	for (auto i = 1; i <= N; i++)
	{
		if (!indegree[i])
		{
			minHeap.insert(i);
		}
	}
	if (true)
	{
		int A, B;
		while (!minHeap.empty())
		{
			A = (*minHeap.begin());
			minHeap.erase(minHeap.begin());
			order.push_back(A);
			for (int i = 0; i < adjList[A].size(); i++)
			{
				B = adjList[A][i];
				--indegree[B];
				if (indegree[B] == 0)
				{
					minHeap.insert(B);
				}
			}
		}
	}
	if (N > order.size())
	{
		cout << "Sandro fails.";
	}
	else {
		for (auto v : order)
		{
			printf("%d ", v);
		}
	}
}

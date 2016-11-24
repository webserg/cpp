#include <iostream>
#include<vector>
#include<set>
#include "least_lexicographic_topological_sort.h"
/*
4 4
1 2
1 3
2 4
3 4
std::ios::sync_with_stdio(false);
*/

using namespace std;
auto test = true;

class Graph
{
	int N, M;
	vector<vector<int>> adjList;
	vector<int> indegree;

public:
	Graph(int n, int m);
	void Graph::addEdge(int x, int y);
	void print();

};

Graph::Graph(int n, int m) :N(n), M(m), adjList(n + 1), indegree(N + 1, 0) {}

void Graph::addEdge(int x, int y)
{
	adjList[x].push_back(y);
	indegree[y]++;
}

void Graph::print()
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
	for (auto k : indegree)
	{
		cout << k << endl;
	}
	cout << endl;
}

inline void keep_window_open()
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	scanf_s("%d", &n);
	scanf_s("%d", &m);
	if (test) {
		cout << "n=" << n << " m=" << m;
	}
	least_lexicographic_topological_sort(n, m, test);
	int x, y;
	if (test) {
		Graph graph(n, m);
		for (auto i = 0; i < m; i++)
		{
			scanf_s("%d", &x);
			scanf_s("%d", &y);
			graph.addEdge(x, y);
		}
		graph.print();
		keep_window_open();
	}
	return 0;
}

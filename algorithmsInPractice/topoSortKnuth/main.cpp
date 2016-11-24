#include <iostream>
#include<vector>
#include<set>
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
void least_lexicographic_topological_sort(const int N, const int M)
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
	//least_lexicographic_topological_sort(n, m);
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

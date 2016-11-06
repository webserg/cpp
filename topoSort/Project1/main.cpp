#include <iostream>
#include<vector>
#include<set>
/*
4 4
1 2
1 3
2 4
3 4
*/

using namespace std;
auto test = false;
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
		for (int i = 0; i < N; i++)
		{
			printf("%d ",order[i]);
		}
	}
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
	int n = 0, m = 0;
	scanf_s("%d", &n);
	scanf_s("%d", &m);
	if (test) {
		cout << "n=" << n << " m=" << m;
	}
	least_lexicographic_topological_sort(n, m);
	if (test) {
		keep_window_open();
	}
	return 0;
}

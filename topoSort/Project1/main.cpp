#include <iostream>
#include<vector>
#include<set>
#define MAXN 100005
using namespace std;

vector<vector<int>> G(MAXN);// Adjacency list representation for a graph
vector<int> indegree(MAXN, 0);//Stores the in-degree of a vertex
vector<int> order;//Stores the least lexicographic ordering of a graph
set<int> minHeap;//min-heap for storing the vertex whose indegree is zero

void least_lexicographic_topological_sort(int N)
{
	//Initially insert all the vertices in heap whise in-degree is zero
	for (int i = 1; i <= N; i++)	{
		if (!indegree[i])		{
			minHeap.insert(i);
		}
	}
	int A, B;
	while (!minHeap.empty())
	{
		A = (*minHeap.begin());
		minHeap.erase(minHeap.begin());
		order.push_back(A);
		for (int i = 0; i<G[A].size(); i++)
		{
			B = G[A][i];
			--indegree[B];
			//If indegree of a particular vertex becomes zero,add it to min-heap
			if (indegree[B] == 0)
			{
				minHeap.insert(B);
			}
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
	//cout << "Please enter an integer value: ";
	//cin >> i;
	//cout << "The value you entered is " << i;
	//cout << " and its double is " << i * 2 << ".\n";
	/*int k = 0;
	vector<vector<int>> vertex(4, vector<int>(4));

	int x=0, y=0;
	for (int i = 0; i < vertex.size(); i++) {
		cin >> x,y;
		vertex[x][y] = 1;
	}
	for (int i = 0; i < vertex.size(); i++) {
		for (int j = 0; j < vertex[i].size(); j++) {
			cout << vertex[i][j] << "\n";
		}
	}*/
	
	/*
	for (int i = 0; i < 10; i++) {
		vector<int> row; // Create an empty row
		for (int j = 0; j < 20; j++) {
			row.push_back(i * j); // Add an element (column) to the row
		}
		; // Add the row to the main vector
	}vertex.push_back(row)
	*/
	int n = 0, m = 0;
	cin >> n;
	cin >> m;
	cout << endl;
	cout << "n=" << n << " m=" << m;
	vector<vector<int>> adjList(n + 1);

	int x = 0, y = 0;
	for (int i = 0; i < m ; i++) {
		cin >> x;
		cin >> y;
		cout << "x=" << x << " y="<< y << endl;
		adjList[x].push_back(y);
	}
	for (int i = 0; i < adjList.size(); i++) {
		cout << i << " -->";
		for (int j = 0; j < adjList[i].size(); j++) {
			cout << adjList[i][j] << ",";
		}
		cout << endl;
	}
	keep_window_open();
	return 0;
}
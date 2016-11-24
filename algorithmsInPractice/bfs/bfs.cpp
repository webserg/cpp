#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "graph_utils.h"
#include "../algo_utils/queue.h"
#define WHITE 0
#define BLACK 1
#define GRAY 2


void bfs(vector<vector<int>> &vertexes, vector<int> &colors, vector<int> &predcessors, vector<int> &distance)
{
	queue<int> Q;
	Q.push(0);
	colors[0] = GRAY;
	while (!Q.empty())
	{
		auto u = Q.pop();
		for (auto v : vertexes[u])
		{
			if (colors[v] == WHITE)
			{
				Q.push(v);
				colors[v] = GRAY;
				predcessors[v] = u;
				distance[v] = distance[u] + 1;
			}
		}
		colors[u] = BLACK;				
	}
}

void printPath(vector<int> &predcessors, int s, int v)
{
	if(s == v)
	{
		cout << s;
	}else if (predcessors[v] == -1){
		cout << " no path from " << s << " to " << v << " \n";
	}
	else
	{
		printPath(predcessors, s, predcessors[v]);
		cout << "-->" << v;
	}
}

int main() {
	ios::sync_with_stdio(false);
	vector<vector<int>> vertexes;
	readGraph(vertexes, "C:\\git\\algorithmsDesignAndAnalysis\\resource\\tinyG.txt");
	printGraph(vertexes);
	vector<int> colors(vertexes.size());
	vector<int> predcessors(vertexes.size());
	for (auto &s : predcessors) { s = -1; }
	vector<int> distance(vertexes.size());
	bfs(vertexes, colors, predcessors, distance);
	for(auto i = 0; i < colors.size(); i++)
	{
		string col = colors[i] == BLACK ? "black" : colors[i] == WHITE ? "white" : "gray";
		cout << i << " " << col << "\n";
	}
	for (auto i = 0; i < predcessors.size(); i++)
	{
		cout << i << " predcessor = " << predcessors[i] << "; distance from 0 = " << distance[i] << "\n";
	}
	printPath(predcessors, 0, 12);
	cout << "\n";

	cin.get();
}

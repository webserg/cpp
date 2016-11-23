#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

inline void readGraph(std::vector<std::vector<int>> &vertexs, string filePath)
{
	auto s = filePath;
	//auto s = "C:\\git\\algorithmsDesignAndAnalysis\\resource\\hashIntTest1.txt";
	ifstream inputFile(s, ios_base::in);
	if (!inputFile.good())
	{
		cout << "file " << s << " not found";
	}
	int V = 0;
	inputFile >> V;
	int E = 0;
	inputFile >> E;
	int u = 0, w = 0;
	vertexs.reserve(V);
	for (int i = 0; i < V; i++)
	{
		vector<int> adjList;
		vertexs.push_back(adjList);
	}
	while (inputFile >> u) {
		inputFile >> w;
		vertexs[u].push_back(w);
	}
	inputFile.close();
}

inline void printGraph(vector<vector<int>> vertexes)
{
	int v = 0;
	for (auto adjList : vertexes)
	{
		cout << v++ << " --> ";
		for (auto w : adjList)
		{
			cout << w << " ";
		}
		cout << "\n";
	}
}

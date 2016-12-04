#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define nl "\n";
inline vector<vector<int>> readGraph(string filePath)
{
	auto s = filePath;
	ifstream inFile(s);
	if (!inFile.good())
		cout << "file " << s << " not found";
	auto V = 0;
	inFile >> V;
	auto E = 0;
	inFile >> E;
	auto u = 0, w = 0;
	auto verteces = vector<vector<int>>(V, vector<int>(V));
	while (inFile >> u)
	{
		if (inFile >> w)
		{
			verteces[u].push_back(w);
		}
	}
	inFile.close();
	return verteces;
}

inline void printGraph(vector<vector<int>> vertexes)
{
	auto v = 0;
	for (auto& adjList : vertexes)
	{
		cout << v++;
		for (auto& w : adjList)
		{
			cout << " -> " << w;
		}
		cout << nl;
	}
}

inline void printGraphToFile(vector<vector<int>> vertexes, string s)
{
	ofstream inFile(s);
	auto v = 0;
	inFile << "digraph G { " << nl;
	for (auto& adjList : vertexes)
	{
		//inFile << v << nl;
		for (auto& w : adjList)
		{
			inFile << v << " -> " << w << nl;
		}
		v++;
		inFile << nl;
	}
	inFile << "}" << nl;
}


#pragma once
#include <iostream>
#include "graph_utils.h"
#include <list>
#define WHITE 0
#define BLACK 1
#define GRAY 2
using namespace std;
class Graph
{
	vector<vector<int>> adjListOfV;
	vector<int> colors;
	vector<int> predcessors;
	vector<int> distance;
	vector<int> finish;
	list<int> topoList;
	int time = 0;
	bool isTree = true;
	void dfs_visit(const int v);
	bool checkIfTree() const;
public:
	explicit Graph(const vector<vector<int>>& vertexes)
		: adjListOfV(vertexes)
	{
		colors.resize(vertexes.size());
		predcessors.resize(vertexes.size());
		for (auto &s : predcessors) { s = -1; }
		distance.resize(vertexes.size());
		finish.resize(vertexes.size());
		//topoList.resize(vertexes.size());
	}
	void dfs();
	bool is_Tree() const
	{
		return isTree;
	};
	void printColors();
	void printTopoList()
	{
		for(auto v : topoList)
		{
			cout << "vertex = " << v << "; f=" << finish[v] << nl;
		}
	}
};
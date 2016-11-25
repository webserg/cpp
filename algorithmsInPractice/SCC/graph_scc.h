#pragma once
#include <iostream>
#include "graph_utils.h"
#include <list>
#include <vector>
#define WHITE 0
#define BLACK 1
#define GRAY 2
using namespace std;
class graph_scc
{
	vector<vector<int>> adjListOfV;
	vector<vector<int>> adjListOfV_T;
	vector<int> colors;
	vector<int> predcessors;
	vector<int> distance;
	vector<int> finish;

	int time = 0;
	bool isTree = true;
	void dfs_visit(const int v);
	bool checkIfTree() const;
public:
	explicit graph_scc(const vector<vector<int>>& vertexes)
		: adjListOfV(vertexes)
	{
		adjListOfV_T.resize(vertexes.size());
		for (auto u = 0; u < vertexes.size(); u++)
		{
			for (auto v : vertexes[u])
			{
				adjListOfV_T[v].push_back(u);
			}
		}
		colors.resize(vertexes.size());
		predcessors.resize(vertexes.size());
		for (auto &s : predcessors) { s = -1; }
		distance.resize(vertexes.size());
		finish.resize(vertexes.size());

	}
	void dfs();
	bool is_Tree() const
	{
		return isTree;
	};
	void printColors();
	const vector<vector<int>>& get_transpose_graph() const
	{
		return adjListOfV_T;
	}
};
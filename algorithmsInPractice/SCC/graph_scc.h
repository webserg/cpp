#pragma once
#include <iostream>
#include "graph_utils.h"
#include <list>
#include <vector>
#define WHITE 0
#define BLACK 1
#define GRAY 2
using namespace std;
//class V
//{
//public:
//	int i;
//	V()
//	{
//		i = 0;
//	}
//	explicit V(int name)
//		: i(name)
//	{
//	}
//
//	operator int()
//	{
//		return i;
//	}
//};
class graph_scc
{
	vector<vector<int>> adjListOfV;
	vector<vector<int>> adjListOfV_T;
	vector<int> colors;
	vector<int> predcessors;
	vector<int> distance;
	vector<int> finish;
	vector<int> leaders_scc;

	int time = 0;
	int k;

	void merge(vector<int>::iterator iter, int first, int mid, int last);

	void split(vector<int>::iterator iter, int first, int last);

	void mergeSort(vector<int>::iterator start, vector<int>::iterator end);

	void dfs_visit(const int v);
	void dfs_visit_scc(const int u);
public:
	explicit graph_scc(const vector<vector<int>>& verteces)
		
	{
		adjListOfV.resize(verteces.size());
		adjListOfV_T.resize(verteces.size());

		for (auto u = 0; u < verteces.size(); u++)
		{
			for (auto v : verteces[u])
			{
				adjListOfV[u].push_back(v);
				adjListOfV_T[v].push_back(u);
			}
		}
		colors.resize(verteces.size());
		predcessors.resize(verteces.size());
		for (auto &s : predcessors) { s = -1; }
		distance.resize(verteces.size());
		finish.resize(verteces.size());

	}
	void dfs();
	void dfs_scc();
	void printColors();
	void printLeaders();
	const vector<vector<int>>& get_transpose_graph() const
	{
		return adjListOfV_T;
	}
};
#include "Graph.h"

void Graph::dfs_visit(const int u)
{
	time++;
	distance[u] = time;
	colors[u] = GRAY;
	for (auto& v : adjListOfV[u])
	{
		if (colors[v] == WHITE)
		{
			predcessors[v] = u;
			dfs_visit(v);
		}
	}
	colors[u] = BLACK;
	time++;
	finish[u] = time;
	topoList.push_front(u);
}


bool Graph::checkIfTree() const
{
	return time < adjListOfV.size() * 2;
}

void Graph::dfs()
{
	for (auto u = 0; u < adjListOfV.size() && checkIfTree(); u++)
	{
		if (colors[u] == WHITE)
		{
			dfs_visit(u);
		}
		if (u > 0)
		{
			isTree = false;
		}
	}
}

void Graph::printColors()
{
	for (auto i = 0; i < colors.size(); i++)
	{
		string col = colors[i] == BLACK ? "black" : colors[i] == WHITE ? "white" : "gray";
		cout << i << " " << col << "\n";
	}
	for (auto i = 0; i < predcessors.size(); i++)
	{
		cout << i << " predcessor = " << predcessors[i] << "; distance from 0 = " << distance[i] << "\n";
	}
}


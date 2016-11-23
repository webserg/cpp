#include <iostream>
#include "graph_utils.h"
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
	void dfs_visit(const int v);
public:
	explicit Graph(const vector<vector<int>>& vertexes)
		: adjListOfV(vertexes)
	{
		colors.resize(vertexes.size());
		predcessors.resize(vertexes.size());
		for (auto &s : predcessors) { s = -1; }
		distance.resize(vertexes.size());
	}
	void dfs();
	void printPath(int s, int v);
	void printColors();
};


void Graph::dfs_visit(const int u)
{
	colors[u] = GRAY;
	for (auto v: adjListOfV[u])
	{
		if(colors[v] == WHITE)
		{
			predcessors[v] = u;
			dfs_visit(v);
		}
	}
	colors[u] = BLACK;
}


void Graph::dfs()
{
	for (auto u = 0; u < adjListOfV.size(); u++)
	{
		if (colors[u] == WHITE)
		{
			dfs_visit(u);
		}
	}
}

void Graph::printPath(int s, int v)
{
	if (s == v)
	{
		cout << s;
	}
	else if (predcessors[v] == -1) {
		cout << " no path from " << s << " to " << v << " \n";
	}
	else
	{
		printPath(s, predcessors[v]);
		cout << "->" << v;
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
int main() {
	ios::sync_with_stdio(false);
	vector<vector<int>> vertexes;
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\dfs\\";
	readGraph(vertexes, dir + "tinyG.txt");
	printGraphToFile(vertexes, dir + "printG.gv");
	auto convertToPNG = "dot -Tpng " + dir + "printG.gv -o " + dir + "printG.png";
	//system(convertToPNG.c_str());
	auto show = dir + "printG.png";
	//system(show.c_str());

	Graph G{vertexes};
	G.dfs();
	G.printPath(0, 11);
	G.printColors();

	cin.get();
	return 0;
}

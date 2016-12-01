#include <iostream>
#include <vector>
#include "graph_scc.h"
using namespace std;

void run_show_graph_command(string dir)
{
	auto convertToPNG = "dot -Tpng " + dir + "printG.gv -o " + dir + "printG.png";
	system(convertToPNG.c_str());
	auto show = dir + "printG.png";
	system(show.c_str());
}

inline void printGraphToFileT(vector<vector<int>> vertexes, string s)
{
	ofstream inFile(s);
	auto v = 0;
	inFile << "digraph G { " << nl;
	for (auto adjList : vertexes)
	{
		//inFile << v << nl;
		for (auto w : adjList)
		{
			inFile << v << " -> " << w << nl;
		}
		v++;
		inFile << nl;
	}
	inFile << "}" << nl;
}

int main() {
	ios::sync_with_stdio(false);
	vector<vector<int>> vertexes;
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\SCC\\";
	readGraph(vertexes, dir + "SCCTest1.txt");
//	printGraphToFile(vertexes, dir + "printG.gv");
//	run_show_graph_command(dir);

	graph_scc G{ vertexes };
//	printGraphToFile(vertexes, dir + "printG.gv");
	printGraphToFileT(G.get_transpose_graph(), dir + "printG.gv");
	run_show_graph_command(dir);

	G.dfs();
	G.dfs_scc();
	//G.printColors();
	cout << "leaders" << "\n";
	G.printLeaders();
	cin.get();
	return 0;
}

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

void test1()
{
	vector<vector<int>> vertexes;
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\SCC\\";
	readGraph(dir + "SCCTest1.txt");
	graph_scc G{ readGraph(dir + "SCCTest1.txt") };
	//	printGraphToFile(vertexes, dir + "printG.gv");
	printGraphToFileT(G.get_transpose_graph(), dir + "printG.gv");
	run_show_graph_command(dir);

	G.dfs();
	G.dfs_scc();
	//G.printColors();
	std::cout << "leaders" << "\n";
	G.printLeaders();

}

void test2(string dir, string file, vector<int> answer, bool drawGraph)
{
	
	graph_scc G{ readGraph(dir + file) };
	if (drawGraph) {
		printGraphToFileT(G.get_transpose_graph(), dir + "printG.gv");
		run_show_graph_command(dir);
	}
	G.dfs();
	G.dfs_scc();
	std::cout << "leaders" << "\n";
	G.printLeaders();
	G.comparesizeSCC(answer);
}

int main() {
	ios::sync_with_stdio(false);
	//	test1();

	test2("C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\SCC\\", "SCCTest2.txt", { 4,3,3,1 }, false);
	test2("C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\SCC\\", "SCCTest3.txt", { 3,3,2 }, false);
	test2("C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\SCC\\", "SCCTest4.txt", { 6,3,2,1 }, false);
	cin.get();
	return 0;
}

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

int main() {
	std::ios::sync_with_stdio(false);
	std::vector<std::vector<int>> vertexes;
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\dfs\\";
	readGraph(vertexes, dir + "tinyG.txt");
//	printGraphToFile(vertexes, dir + "printG.gv");
//	run_show_graph_command(dir);

	graph_scc G{ vertexes };
	printGraphToFile(G.get_transpose_graph(), dir + "printG.gv");
	run_show_graph_command(dir);

	G.dfs();
	G.printColors();
	std::cin.get();
	return 0;
}

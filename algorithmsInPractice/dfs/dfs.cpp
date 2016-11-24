#define BOOST_TEST_MODULE Dfs Test suites
#include <boost/test/included/unit_test.hpp>
#include "Graph.h"

BOOST_AUTO_TEST_CASE(tineG_graph_test)
{
	ios::sync_with_stdio(false);
	vector<vector<int>> vertexes;
	string dir = "C:\\git\\algorithmsDesignAndAnalysis\\resource\\";
	readGraph(vertexes, dir + "tinyG.txt");
	Graph G{ vertexes };
	G.dfs();
	BOOST_CHECK(G.is_Tree(),"it is tree");
}

BOOST_AUTO_TEST_CASE(tineG_tree_test)
{
	ios::sync_with_stdio(false);
	vector<vector<int>> vertexes;
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\dfs\\";
	readGraph(vertexes, dir + "tinyG.txt");
	Graph G{ vertexes };
	G.dfs();
	BOOST_CHECK(!G.is_Tree(), "it is graph, but not tree");
}
BOOST_AUTO_TEST_CASE(main_test)
{
	ios::sync_with_stdio(false);
	vector<vector<int>> vertexes;
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\dfs\\";
	readGraph(vertexes, dir + "tinyG.txt");
	printGraphToFile(vertexes, dir + "printG.gv");
	auto convertToPNG = "dot -Tpng " + dir + "printG.gv -o " + dir + "printG.png";
	//system(convertToPNG.c_str());
	auto show = dir + "printG.png";
	//system(show.c_str());

	Graph G{ vertexes };
	G.dfs();
	if(G.is_Tree())
	{
		cout << "it is tree" << nl;
	}else
	{
		cout << "it is graph, but not tree" << nl;
	}
	G.printColors();

	cin.get();
}

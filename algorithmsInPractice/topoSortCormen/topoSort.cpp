#define BOOST_TEST_MODULE Topo sort Test suites
#include <boost/test/included/unit_test.hpp>
#include "../dfs/Graph.h"
#include "../dfs/Graph.cpp"
namespace utf = boost::unit_test;
const bool main_run = false;


BOOST_AUTO_TEST_CASE(topoSort_test)
{
	ios::sync_with_stdio(false);
	vector<vector<int>> vertexes;
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\dfs\\";
	readGraph(vertexes, dir + "topoSortCormen1.txt");
	Graph G{ vertexes };
	G.dfs();
	cout << "finish" << nl;
	G.printTopoList();
}

BOOST_AUTO_TEST_CASE(main_test, * utf::enable_if<main_run>())
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
	if (G.is_Tree())
	{
		cout << "it is tree" << nl;
	}
	else
	{
		cout << "it is graph, but not tree" << nl;
	}
	G.printColors();

	
}

BOOST_AUTO_TEST_CASE(show_res_test)
{
	cin.get();
}

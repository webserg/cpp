
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <iterator>
#include <sstream>
using namespace std;


vector<int> unionFindFastUnionWeighted(int V, vector<pair<int, int>>& edges)
{
	auto id = vector<int>(V);
	auto sz = vector<int>(V);
	for (auto i = 0; i < V; i++)
	{
		id[i] = i; sz[i] = 1;
	}
	for (auto& p : edges)
	{
		auto u = id[p.first];
		auto v = id[p.second];
		for (; u != id[u]; u = id[u]);
		for (; v != id[v]; v = id[v]);
		if (u == v) continue;
		if (sz[u] < sz[v])
		{
			id[u] = v;
			sz[u] += sz[v];
		}
		else
		{
			id[v] = u;
			sz[v] += sz[u];
		}

		cout << u << " " << v << " \n";
	}
	return id;
}

vector<int> unionFindFastUnion(int V, vector<pair<int, int>>& edges)
{
	auto id = vector<int>(V);
	for (auto i = 0; i < V; i++)
	{
		id[i] = i;
	}
	for (auto& p : edges)
	{
		auto u = id[p.first];
		auto v = id[p.second];
		for (; u != id[u]; u = id[u]);
		for (; v != id[v]; v = id[v]);
		if (u == v) continue;
		id[u] = v;
		cout << u << " " << v << " \n";
	}
	return id;
}


vector<int> unionFindFastSearch(int V, vector<pair<int, int>>& edges)
{
	auto id = vector<int>(V);
	for (auto i = 0; i < V; i++)
	{
		id[i] = i;
	}
	for (auto& p : edges)
	{
		auto t = id[p.first];
		if (t == id[p.second])
		{
			continue;
		}
		else
		{
			for (auto i = 0; i < V; i++)
			{
				if (id[i] == t)
				{
					id[i] = id[p.second];
				}
			}
			cout << p.first << " " << p.second << " \n";
		}

	}
	return id;
}

void readEdges(std::string filePath, int& V, vector<pair<int, int>>& edges)
{
	auto s = filePath;
	std::ifstream inFile(s);
	if (!inFile.good())
		cout << "file not found";
	V = 0;
	inFile >> V;
	auto E = 0;
	inFile >> E;
	auto u = 0, w = 0;
	edges = vector<pair<int, int>>();
	while (inFile >> u >> w)
	{
		edges.push_back(pair<int, int>(u, w));
	}
	inFile.close();
}

string toStr(vector<int> res)
{
	std::stringstream ss;
	for (size_t i = 0; i < res.size(); ++i)
	{
		if (i != 0)
			ss << " ";
		ss << res[i];
	}
	return 	ss.str();
}

inline void unionFindTest(std::string filePath)
{
	int V;
	vector<pair<int, int>> edges;
	readEdges(filePath, V, edges);
	for (auto& p : edges)
	{
		//cout << p.first << " " << p.second << "\n";
	}
	auto res = unionFindFastSearch(V, edges);
	auto s = toStr(res);
	cout << s <<"\n";
	assert(s.compare("1 1 1 1 1 1 1 1 1 1") == 0);
}

inline void unionFindTest2(std::string filePath)
{
	int V;
	vector<pair<int, int>> edges;
	readEdges(filePath, V, edges);
	for (auto& p : edges)
	{
		//cout << p.first << " " << p.second << "\n";
	}
	auto res = unionFindFastUnion(V, edges);
	auto s = toStr(res);
	cout << s << "\n";
	assert(s.compare("1 1 9 4 9 6 9 9 0 0") == 0);
}

inline void unionFindTest3(std::string filePath)
{
	int V;
	vector<pair<int, int>> edges;
	readEdges(filePath, V, edges);
	for (auto& p : edges)
	{
		//cout << p.first << " " << p.second << "\n";
	}
	auto res = unionFindFastUnionWeighted(V, edges);
	auto s = toStr(res);
	cout << s << "\n";
	assert(s.compare("8 7 5 2 3 7 5 7 7 3") == 0);
}
int main()
{
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\unionFind\\";
	std::ios::sync_with_stdio(false);
	unionFindTest(dir + "unionFindTest1.txt");
	unionFindTest2(dir + "unionFindTest1.txt");
	unionFindTest3(dir + "unionFindTest1.txt");

	std::cin.get();
	return 0;
}

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
inline void unionFindTest(std::string filePath)
{
	auto s = filePath;
	std::ifstream inFile(s);
	if (!inFile.good())
		cout << "file not found";
	auto V = 0;
	inFile >> V;
	auto E = 0;
	inFile >> E;
	auto u = 0, w = 0;
	auto edges = vector<pair<int, int>>();
	while (inFile >> u >> w)
	{
		edges.push_back(pair<int, int>(u, w));
	}
	inFile.close();
	for (auto& p : edges)
	{
		//cout << p.first << " " << p.second << "\n";
	}
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
			for (auto i = 0; i < V; i++)
			{
				if (id[i] == t) {
					cout << i << " ";
				}
			}
			cout << "\n";
			continue;
		}
		else
		{
			for (auto i = 0; i < V; i++)
			{
				if(id[i] == t)
				{
					id[i] = id[p.second];
				}
			}
			cout << p.first << " " << p.second << " \n";
		}

	}
	for (auto i = 0; i < V; i++)
	{
		cout << id[i] << "\n";
	}
}
int main()
{
	string dir = "C:\\Users\\webse\\Source\\Repos\\cpp\\algorithmsInPractice\\unionFind\\";
	std::ios::sync_with_stdio(false);
	unionFindTest(dir + "unionFindTest1.txt");
	std::cin.get();
	return 0;
}
#include <iosfwd>
#include <vector>
#include <iostream>
#include  "mergeSort.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	vector<int> vertexes{ 2,9,8,7,6,3,1,0,78,18,19,20,0 };


	mergeSort(vertexes.begin(), vertexes.end());
	cout << "\n";
	for (auto v : vertexes)
	{
		cout << v << " ";
	}
	cout << "\n";
	std::cin.get();
	return 0;
}

#include <iostream>
#include "graph_utils.h"
void test_linked_list()
{
	linked_list list;
	list.add(1);
	list.add(2);
	list.add(3);
	list.print();
}
int main() {
	//C:\Users\webse\Source\Repos\cpp\algorithmsInPractice\dfs
	std::ios::sync_with_stdio(false);
	test_linked_list();
	std::cin.get();
	return 0;
}

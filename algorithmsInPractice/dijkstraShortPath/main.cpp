#include<iostream>
#include<array>
#include<vector>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <chrono>
using namespace std;
void error(string s)
{
	throw runtime_error(s);
}
class Vertex
{
	int name;
	int key;
public:
	explicit Vertex(int n, int s);
	int getName()const;
	int getKey()const;
	void setKey(int k)
	{
		key = k;
	}
	friend std::ostream& operator<< (std::ostream &out, const Vertex &v);
};


class MinHeap
{
	int counter = 0;
	vector<int> indexes;
public:
	explicit MinHeap(int n);
	static int parent(int);
	int left(int) const;
	int right(int) const;
	//void insert(Vertex&);
	void minHeapify(vector<Vertex> &A, int i);
	void exchange(vector<Vertex> &A, int i, int j);
	void buildHeap(vector<Vertex> &A);
	Vertex extractMin(vector<Vertex> &A);
	void decreaseKey(vector<Vertex> &A, int, int);
	int getIndexByName(int n) { return indexes[n]; };
};

Vertex::Vertex(int n, int s) : name(n), key(s)
{
}

int Vertex::getName() const
{
	return name;
}

int Vertex::getKey() const
{
	return key;
}

std::ostream& operator<< (std::ostream &out, const Vertex &v)
{
	out << "Vertex(" << v.getName() << ", " << v.getKey() << ")";
	return out;
}

MinHeap::MinHeap(int n) : counter(n), indexes(n + 1)
{

}

int MinHeap::parent(int v)
{
	if (v > 1) {
		return v / 2;
	}
	else if (v == 1) {
		return 0;
	}
	else {
		return -1;
	}
}

int MinHeap::left(int v) const
{
	if (v == 0) return 1;
	else if (2 * v < counter) {
		return 2 * v;
	}
	return -1;
}

int MinHeap::right(int v) const
{
	if (v == 0) return 2;
	else if (2 * v + 1 < counter) {
		return 2 * v + 1;
	}
	return -1;
}

void MinHeap::minHeapify(vector<Vertex>& A, int i)
{
	auto l = left(i);
	auto r = right(i);
	int smallest;
	if (l < A.size() && l > 0 && A[l].getKey() < A[i].getKey()) {
		smallest = l;
	}
	else smallest = i;
	if (r < A.size() && r > 0 && A[r].getKey() < A[smallest].getKey()) {
		smallest = r;
	} if (smallest != i) {
		exchange(A, i, smallest);
		minHeapify(A, smallest);
	}
}

void MinHeap::exchange(vector<Vertex>& A, int i, int j)
{
	indexes[A[i].getName()] = j;
	indexes[A[j].getName()] = i;
	iter_swap(A.begin() + i, A.begin() + j);
}

void MinHeap::buildHeap(vector<Vertex>& A)
{
	counter = A.size();
	int i = 0;
	for (auto v:A)
	{
		indexes[v.getName()] = i++;
	}

	for (int i = counter / 2; i >= 0; i--)
	{
		minHeapify(A, i);
	}
}

Vertex MinHeap::extractMin(vector<Vertex>& A)
{
	if (counter < 1)
	{
		error("heap underflow");
	}
	auto min = A[0];
	exchange(A, 0, counter - 1);
	counter--;
	A.erase(A.end() - 1);
	minHeapify(A, 0);
	return min;
}

void MinHeap::decreaseKey(vector<Vertex>& A, int vertexName, int newKey)
{
	auto i = indexes[vertexName];
	if (i > counter) return;
	if (newKey < A[i].getKey())
	{
		A[i].setKey(newKey);
	}
	while (i > 0 && parent(i) >= 0 && A[parent(i)].getKey() > A[i].getKey())
	{
		exchange(A, i, parent(i));
		i = parent(i);
	}
}

void printLength(const array<int, 10>& myarray)
{
	cout << "length: " << myarray.size() << endl;
}

void printarray(int arg[], int length) {
	for (auto n = 0; n < length; ++n)
		cout << arg[n] << ' ';
	cout << '\n';
}

void testarray()
{
	array<int, 10> myarray{ 16,14,10,8,7,9,3,2,4,1 };
	printLength(myarray);
	for (const auto& element : myarray)

		//sort(myarray.begin(), myarray.end()); // sort the array forwards
		sort(myarray.rbegin(), myarray.rend()); // sort the array backwards

	for (const auto& element : myarray)
		std::cout << element << ' ';
	cout << '\n';
}

void testRemovingFromVector()
{
	vector<int> myvector;

	// now here's the concise version
	auto start = chrono::system_clock::now();
	// benchmark something here
	auto end = chrono::system_clock::now();

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++) myvector.push_back(i);

	// erase the 6th element
	myvector.erase(myvector.begin() + 5);
	myvector.erase(myvector.begin() + 5);
	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	// erase the first 3 elements:
	myvector.erase(myvector.begin(), myvector.begin() + 3);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}

void testHeapLeft()
{
	//int a = std::numeric_limits<int>::max();
	int foo[5] = { 16, 2, 77, 40, 12 };
	vector<Vertex> A{ Vertex(1,16), Vertex(2,2), Vertex(3,77), Vertex(4,40), Vertex(5,12),Vertex(6,7),Vertex(7,8) };

	auto heap = MinHeap(5);

	//printarray(foo, 5);
	//for (auto x : foo) heap.insert(Vertex(i++,x));
	auto l = heap.left(0);
	assert(A[l].getName() == 2);
	assert(A[heap.right(0)].getName() == 3);
	//auto p = heap.parent(vs[0]);
	auto t = A[heap.left(1)].getKey();
	assert(t == 77, "left");
	assert(A[heap.right(1)].getKey() == 40, "right");
	//assert(heap.parent(1).getIdx() == 0);
	//heap.exchange(A, 0, 1);
	//assert(A[0].getName() == 2);
	heap.buildHeap(A);
	for (auto i = 0; i < A.size(); ++i)
		cout << ' ' << A[i];
	cout << '\n';

	heap.decreaseKey(A, 6, 5);
	for (auto i = 0; i < A.size(); ++i)
		cout << ' ' << A[i];
	cout << '\n';

	int size = A.size();
	cout << ' ' << heap.extractMin(A);
	for (auto i = 0; i < size - 1; ++i)
		cout << ' ' << heap.extractMin(A);
	cout << '\n';

}

void runDijkstra(const int n, vector<vector<pair<int, int>>> &adjList)
{
	int source = 1;
	int noWay = numeric_limits<int>::max();
	const auto N = n;
	for (int destitation = 2; destitation <= N; ++destitation) {

		vector<Vertex> A;
		A.reserve(N);
		auto heap = MinHeap(N);
		for (auto i = 0; i < N; i++) {
			A.push_back(Vertex(i + 1, noWay));
		}

		for (auto p : adjList[source]) {
			A[p.first - 1].setKey(p.second);
		}
		heap.buildHeap(A);
		auto cur = source;
		int shortWay = noWay;
		while (cur != destitation) {
			try {
				auto min = heap.extractMin(A);

				cur = min.getName();
				shortWay = min.getKey();
				for (auto p : adjList[min.getName()])
				{
					heap.decreaseKey(A, p.first, shortWay + p.second);
				}

			}

			catch (runtime_error) {
				cout << noWay;
				return;
			}

		}
		cout << shortWay << "\n";
	}
}

void testPairs()
{
	int noWay = numeric_limits<int>::max();
	const auto N = 5;
	vector<Vertex> A;
	A.reserve(N);
	auto v = make_pair(1, 25);
	for (auto i = 0; i < N; i++) {
		A.push_back(Vertex(i + 1, noWay));
	}
	vector<vector<pair<int, int>>> adjList = {
		{},
		{ { 2, 10 },{ 4,  30 },{ 5, 100 } },
		{ { 3,  50 } },
		{ { 5, 10 } },
		{ { 3,  20 },{ 5, 60 } },
		{}
	};
	vector<int> indexes = { 0,1,2,3,4,5 };
	A[4 - 1].setKey(60);
	for (int i = 0; i < adjList.size(); ++i) {
		cout << i;
		for (auto p : adjList[i])
		{
			cout << " " << p.first << "," << p.second;
		}
		cout << "\n";
	}

}

void runTests()
{
	testHeapLeft();
}

void testCase1()
{
	cout << "test case 1\n";
	vector<vector<pair<int, int>>> adjList = {
		{},
		{ { 2, 10 },{ 4,  30 },{ 5, 100 } },
		{ { 3,  50 } },
		{ { 5, 10 } },
		{ { 3,  20 },{ 5, 60 } },
		{}
	};
	runDijkstra(5, adjList);
}
void testCase2()
{
	cout << "test case 2\n";
	vector<vector<pair<int, int>>> adjList = {
		{},
		{ { 2, 50 }, { 3,  10 },{ 5,45 } },
		{ { 5,  10 } },
		{ { 1, 20 }, {4,15} },
		{ { 2,  20 }, { 5, 35 } },
		{ { 4, 30 } },
		{ { 4 ,3 } }
	};
	runDijkstra(6, adjList);
}
int main()
{
	ios::sync_with_stdio(false);
	//testarray();
	//testRemovingFromVector();
	//runTests();
	//testPairs();
	testCase1();
	testCase2();
	cin.get();
}

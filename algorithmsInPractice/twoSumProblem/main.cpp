#include <iostream>
#include <fstream>
#include <cvt/wstring>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <thread>
#include <atomic>
#include <mutex>
#include "hash_set.h"
#include "concurrent_hash_set.h"

using namespace std;

void readNumbers(hash_set &mset)
{
	auto s = "C:\\git\\algorithmsDesignAndAnalysis\\resource\\2sum.txt";
	//auto s = "C:\\git\\algorithmsDesignAndAnalysis\\resource\\hashIntTest1.txt";
	ifstream inputFile(s, ios_base::in);
	if (!inputFile.good())
	{
		cout << "file " << s << " not found";
	}

	string number;

	while (!inputFile.eof()) {
		inputFile >> number;
		mset.insert(stoll(number));
	}

	inputFile.close();

}

void do_work(hash_set& mset, int& res, hash_set& tset, int t)
{
	for (auto y : mset.iter)
	{
		auto x = t - y;
		auto xMinusYPlus = y > 0 && x < 0;
		auto yMinusXPlus = y < 0 && x > 0;

		if (xMinusYPlus || yMinusXPlus) {
			if (mset.contains(x) && x != y && !tset.contains(t)) {
				tset.insert(t);
				res++;
				//printf("%.1lf + %.1lf = %d, count= %d\n", y, x, t, res);
			}
		}
	}
}


class Res
{
	atomic<int> x;

public:
	Res() {
		x = 0;
	}
	void Add() {
		++x;
	}
	void Sub() {
		--x;
	}
	int get() {
		return x;
	}
};

void do_work_concurent(hash_set& mset, Res& res, concurrent_hash_set& tset, int t)
{
	for (auto y : mset.iter)
	{
		auto x = t - y;
		auto xMinusYPlus = y > 0 && x < 0;
		auto yMinusXPlus = y < 0 && x > 0;

		if (xMinusYPlus || yMinusXPlus) {
			if (mset.contains(x) && x != y && !tset.contains(t)) {
				res.Add();
				//printf("%lld + %lld = %d, count= %d\n", y, x, t, res.get());
				tset.insert(t);
			}
		}
	}
}

struct WorkingFunctionInThread
{
	Res &res;
	hash_set& mset;
	concurrent_hash_set& tset;
	int startRange;
	int endRange;
	WorkingFunctionInThread(Res& res, hash_set& mset, concurrent_hash_set& tset, int startRange, int endRange) :
		res{ res }, mset{ mset }, tset{ tset }, startRange{ startRange }, endRange{ endRange } {}
	void operator()()
	{
		cout << "tread started \n";
		for (auto t = startRange; t < endRange; t++)
		{
			do_work_concurent(mset, res, tset, t);
		}
		cout << "tread finished \n";
	}
};


void countTwoSum_concurrent(hash_set &mset, int startRange, int endRange, Res& res)
{
	auto i = 0;
	concurrent_hash_set tset(500);
	WorkingFunctionInThread my_func(res, mset, tset, startRange, startRange / 2);
	thread my_thread(my_func);
	thread_guard g(my_thread);

	WorkingFunctionInThread my_func2(res, mset, tset, startRange / 2, 0);
	thread my_thread2(my_func2);
	thread_guard g1(my_thread2);

	WorkingFunctionInThread my_func3(res, mset, tset, 0, endRange / 2);
	thread my_thread3(my_func3);
	thread_guard g2(my_thread3);

	WorkingFunctionInThread my_func4(res, mset, tset, endRange / 2, endRange + 1);
	thread my_thread4(my_func4);
	thread_guard g3(my_thread4);

}

void countTwoSum(hash_set &mset, int startRange, int endRange)
{
	auto i = 0;
	auto res = 0;
	hash_set tset(1000);
	for (auto t = startRange; t < startRange / 2; t++)
	{
		do_work(mset, res, tset, t);
	}
	for (auto t = startRange / 2; t < 0; t++)
	{
		do_work(mset, res, tset, t);
	}
	for (auto t = 0; t < endRange / 2; t++)
	{
		do_work(mset, res, tset, t);
	}
	for (auto t = endRange / 2; t <= endRange; t++)
	{
		do_work(mset, res, tset, t);
	}
	cout << "res=" << res << "\n";
}


void twoSumProblem()
{
	auto N = 1000000;
	hash_set mSet(N);
	readNumbers(mSet);
	cout << "number loaded " << "\n";
	//countTwoSum(mSet, -10000, 10000);
	Res res;
	countTwoSum_concurrent(mSet, -10000, 10000, res);

	cout << "res=" << res.get() << "\n";
	cout << "\n" << "end";//427
}

void testSet()
{
	cout << std::hash<int>()(1) << endl;
	using namespace stdext;
	typedef unordered_set<int> MySet;
	unordered_set <int> hs1;
	unordered_set <int>::iterator hs1_Iter;
	unordered_set <int>::const_iterator hs1_cIter;


	hs1.insert(1);
	hs1.insert(2);
	hs1.insert(3);

	hs1_Iter = hs1.begin();
	cout << "The first element of hs1 is " << *hs1_Iter << endl;

	hs1_Iter = hs1.begin();
	hs1.erase(hs1_Iter);

	// The following 2 lines would err because the iterator is const  
	// hs1_cIter = hs1.begin( );  
	// hs1.erase( hs1_cIter );  

	hs1_cIter = hs1.begin();
	auto elem = hs1.find(3);
	cout << "The first element of hs1 is now " << *hs1_cIter << endl;
	if (elem != hs1.end())
		cout << *elem;
	if (hs1.count(2)) {
		std::cout << "Found\n";
	}
	else {
		std::cout << "Not found\n";
	}
	MySet myset;
	myset.insert(1);
	myset.insert(1);
	myset.insert(1);
	cout << myset.count(1) << "\n";
	cout << myset.size() << "\n";
}


void testMySet()
{
	cout << std::hash<int>()(1) << endl;
	hash_set myset(10);

	myset.insert(1);
	myset.insert(1);
	myset.insert(1);
	myset.insert(2);
	myset.insert(3);
	myset.insert(5);
	myset.insert(6);
	myset.insert(7);
	myset.insert(8);
	myset.insert(9);
	myset.insert(10);
	myset.insert(11);
	if (myset.contains(1))
		cout << 1 << " exists" << "\n";
	if (!myset.contains(12)) {
		cout << 12 << " doesnt exists" << "\n";
	}
	cout << myset.contains(4) << "\n";
	for (auto e : myset.iter) {
		cout << e << " contains - " << myset.contains(e) << "\n";
	}
}


void testMultiSet()
{
	using namespace stdext;
	typedef multiset<int> MySet;

	MySet myset;
	myset.insert(1);
	myset.insert(1);
	myset.insert(1);
	myset.insert(3);
	myset.insert(4);
	myset.insert(1);
	for (auto it = myset.begin(); it != myset.end(); ++it)
	{
		auto count = myset.count(7);
		if (count)
		{
			cout << (*it) << " cout = " << count << "\n";
		}
	}
	cout << myset.count(1) << "\n";
	cout << myset.size() << "\n";

}
void testmap()
{
	unordered_map<string, int> mapOfWords;
	// Inserting data in std::map
	mapOfWords.insert(std::make_pair("earth", 1));
	mapOfWords.insert(std::make_pair("moon", 2));
	mapOfWords["upiter"]++;
	mapOfWords["pluto"]++;
	mapOfWords["saturn"]++;
	mapOfWords["saturn"]++;
	mapOfWords["saturn"]++;
	cout << mapOfWords["moon"] << "\n";
	cout << mapOfWords["saturn"] << "\n";
	mapOfWords["sun"] = 3;
	// Will replace the value of already added key i.e. earth
	mapOfWords["earth"] = 4;
	// Iterate through all elements in std::map
	cout << mapOfWords["something"] << "\n";
	cout << mapOfWords.count("www") << "\n";
	auto it = mapOfWords.begin();
	while (it != mapOfWords.end())
	{
		std::cout << it->first << " :: " << it->second << std::endl;
		++it;
	}
	// Check if insertion is successful or not
	if (mapOfWords.insert(std::make_pair("earth", 1)).second == false)
	{
		std::cout << "Element with key 'earth' not inserted because already existed" << std::endl;
	}
	// Searching element in std::map by key.
	if (mapOfWords.find("sun") != mapOfWords.end())
		std::cout << "word 'sun' found" << std::endl;
	if (mapOfWords.find("mars") == mapOfWords.end())
		std::cout << "word 'mars' not found" << std::endl;

}

void hello(Res& a)
{
	a.Add();
	//std::cout << "Hello Concurrent World from " << " i= " << "\n";
}

struct WorkingFunc
{
	Res &i;
	WorkingFunc(Res& i_) :i(i_) {}
	void operator()()
	{
		for (unsigned j = 0; j < 10000; ++j)
		{
			hello(i);
		}
	}
};

void oops(Res &a)
{

	WorkingFunc my_func(a);
	thread my_thread(my_func);
	thread_guard g(my_thread);
	//std::thread my_thread1(my_func);
	thread my_thread2(my_func);
	thread_guard g2(my_thread2);
	thread my_thread3(my_func);
	thread_guard g3(my_thread3);
	thread my_thread4(my_func);
	thread_guard g4(my_thread4);

}
int testThread()
{
	atomic<int> j = 0;
	Res a;
	oops(a);
	std::cout << "res" << " i= " << a.get() << "\n";

	std::cout << "res" << " i= " << a.get() << "\n";

	//my_thread1.join();
	std::cout << "res" << " i= " << a.get() << "\n";


	std::cout << "res" << " i= " << a.get() << "\n";
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	//twoSumProblem();
	//testSet();
	//testMultiSet();
	//testmap();
	//testMySet();
	testThread();
	cin.get();
	return 0;
}

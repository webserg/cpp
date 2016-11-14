#include <iostream>
#include <fstream>
#include <cvt/wstring>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;
class hash_set
{
	vector<vector<long long>> elems;
	int N;
	float load_factor = 0.75;
	int size;
	int getIdx(long long) const;
public:
	vector<long long> iter;
	explicit hash_set(int n) :N(n)
	{
		size = N * load_factor;
		elems.reserve(size);
		iter.reserve(N);
		vector<long long> empty;
		for (int i = 0; i < size; ++i)
		{
			elems.push_back(empty);
		}
	};

	void insert(long long);
	int contains(long long);

};

int hash_set::getIdx(long long d) const
{
	int h = hash<double>()(d);
	return h % elems.size();
}

void hash_set::insert(long long d)
{
	iter.push_back(d);
	elems[getIdx(d)].push_back(d);
}

int hash_set::contains(long long d)
{
	for (auto e : elems[getIdx(d)])
	{
		if (e == d) return 1;
	}
	return 0;
}

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

void countTwoSum(hash_set &mset, int startRange, int endRange)
{
	auto i = 0;
	auto res = 0;
	hash_set tset(1000);
	for (auto y : mset.iter)
	{
		for (auto t = startRange; t <= endRange; t++) {
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
	cout << "res=" << res << "\n";
}


void twoSumProblem()
{
	auto N = 1000000;
	hash_set mSet(N);
	readNumbers(mSet);
	//countTwoSum(mSet, -10000, 10000);
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

	myset.insert(1.0);
	myset.insert(1.0);
	myset.insert(1.0);
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

int main() {
	ios::sync_with_stdio(false);
	twoSumProblem();
	//testSet();
	//testMultiSet();
	//testmap();
	//testMySet();
	cin.get();
	return 0;
}

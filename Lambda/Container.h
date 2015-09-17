#pragma once
#include "main.h"
template<typename T> class allocator {
public:	
	T* allocate(int n); // allocate space for n objects of type T
	void deallocate(T* p, int n); // deallocate n objects of type T starting at p
	void construct(T* p, const T& v); // construct a T with the value v in p
	void destroy(T* p); // destroy the T in p
};
template<typename T> class Container
{
private:
	int sz;
	T* elem;
	int space;// number of elements plus “free space”/“slots”
// for new elements (“the current allocation”)
	void copy(const Container& arg);     // copy elements from arg into *elem
public:
	Container();
	explicit Container(int s);
	~Container()
	{
		cout << "destructor delete[] elem\n";
		delete[] elem;
	}
	Container(const Container& c);//copy constuctor
	Container& operator=(const Container&);
	T& operator[](int n) { return elem[n]; }
	const T& operator[](int n) const { return elem[n]; } // for const vectors
	Container(Container&&); // move constructor
	Container& operator=(Container&&); // move assignment
	int size() const {
		return sz;
	}
	void print() const;
	void set(int pos, T val);
	void reserve(int newalloc);
	int capacity() const;
	void resize(int newsize);
	void push_back(const T d);
};
struct Link {
	string value;
	Link* prev;
	Link* succ;
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } { }
	Link* insertBefore(Link* n);
	Link* addAfter(Link* n);
	Link* erase(); // remove this object from list
	Link* find(const string& s); // find s in list
	
	Link* advance(int n) const; // move n positions in list
	void print() const;
};


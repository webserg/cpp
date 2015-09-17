#include "Container.h"

using namespace std;
class myexception : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;

template<typename T> Container<T>::Container() : sz{ 0 }, elem{ nullptr }, space{ 0 }
{
	cout << "default constructor \n";
}

template<typename T> Container<T>::Container(int s) : sz{ s }, space{ s }, elem{ new double[s] }
{
	cout << "constructor(int s) \n";
	for (int i = 0; i < s; ++i) { elem[i] = 0; }
}

template<typename T> Container<T>::Container(const Container<T>& c) : sz{ c.size() }, space{ c.size() }, elem{ new T[c.size()] } {
	cout << "copy constructor\n";
	copy(c);
}

template<typename T> Container<T>::Container(Container<T>&& a)
	: sz{ a.sz }, elem{ a.elem } // copy a’s elem and sz
{
	cout << "move constructor \n";
	a.sz = 0; // make a the empty vector
	a.elem = nullptr;
}

template<typename T> void Container<T>::copy(const Container<T>& arg) {
	for (int i = 0; i < arg.sz; ++i) elem[i] = arg.elem[i];
}


template<typename T> Container<T>& Container<T>::operator=(const Container<T>& a)
{
	cout << " copy(operator) a to this vector \n";
	if (this == &a) return *this; // self-assignment, no work needed
	if (a.sz <= space) { // enough space, no need for new allocation
		for (int i = 0; i < a.sz; ++i) elem[i] = a.elem[i]; // copy elements
		sz = a.sz;
		return *this;
	}
	T* p = new T[a.sz]; // allocate new space
	for (int i = 0; i < a.sz; ++i) p[i] = a.elem[i]; // copy elements
	delete[] elem; // deallocate old space
	space = sz = a.sz; // set new size
	elem = p; // set new elements
	return *this;
}

template<typename T> Container<T>& Container<T>::operator=(Container<T>&& a) // move a to this vector
{
	cout << " move(operator) a to this vector \n";
	delete[] elem; // deallocate old space
	elem = a.elem; // copy a’s elem and sz
	sz = a.sz;
	a.elem = nullptr; // make a the empty vector
	a.sz = 0;
	return *this; // return a self-reference (see §17.10)
}

template<class T> 
void Container<T>::set(int pos, T val) {
	elem[pos] = val;
}

template<typename T> void Container<T>::print() const {
	cout << "Container: ";
	for (int i = 0; i < sz; i++) {
		cout << elem[i] << " ";
	}
	cout << "\n";

}

template<typename T> void Container<T>::reserve(int newalloc)
{
	if (newalloc <= space) return; // never decrease allocation
	T* p = new T[newalloc]; // allocate new space
	for (int i = 0; i < sz; ++i) p[i] = elem[i]; // copy old elements
	delete[] elem; // deallocate old space
	elem = p;
	space = newalloc;
}

template<typename T> int Container<T>::capacity() const { return space; }

template<typename T> void Container<T>::resize(int newsize)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
	if (newsize < capacity()) {
		throw myex;
	}
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) elem[i] = 0; // initialize new elements
	sz = newsize;
}

template<typename T> void Container<T>::push_back(const T d)
// increase vector size by one; initialize the new element with d
{
	if (space == 0)
		reserve(8); // start with space for 8 elements
	else if (sz == space)
		reserve(2 * space); // get more space
	elem[sz] = d; // add d at end
	++sz; // increase the size (sz is the number of elements)
}

Link* Link::insertBefore(Link* n) // insert n before this
{
	if (n == nullptr) return this;
	//if (p == nullptr) return n;
	n->succ = this; // p comes after n
	if (prev) prev->succ = n; // n comes after what used to be p’s predecessor
	n->prev = prev; // p’s predecessor becomes n’s predecessor
	prev = n; // n becomes p’s predecessor
	return n;
}

Link* Link::addAfter(Link* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->prev = this;
	if (succ) {
		succ->prev = n;
	}
	n->succ = succ;
	succ = n;
	return n;
}
Link* Link::erase() {
	if (prev) {
		prev->succ = succ;
	}
	if (succ) {
		succ->prev = prev;
	}
	return succ;
}

Link* Link::find(const string& s) {
	if (value == s) return this;
	Link* curr = this;
	while (curr->prev) {
		curr = curr->prev;
	}

	while (curr) {
		if (curr->value == s) return curr;
		curr = curr->succ;
	}
	return nullptr;
}

void Link::print() const {
	if (prev == nullptr) {
		cout << "null <- ";
	}
	else {
		cout << " <- ";
	}
	cout << value << " ";
	if (succ) {
		succ->print();
	}
}
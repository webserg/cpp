#include "Container.h"

using namespace std;

class myexception : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;

Container<double>::Container() : sz{ 0 }, elem{ nullptr }, space{ 0 }
{
	cout << "default constructor \n";
}

Container<double>::Container(int s) : sz{ s }, space{ s }, elem { new double[s] }
{
	cout << "constructor(int s) \n";
	for (int i = 0; i < s; ++i) { elem[i] = 0; }
}

Container<double>::Container(const Container<double>& c) : sz{ c.size() }, space{ c.size() }, elem{ new double[c.size()] } {
	cout << "copy constructor\n";
	copy(c);
}

Container<double>::Container(Container<double>&& a)
	: sz{ a.sz }, elem{ a.elem } // copy a’s elem and sz
{
	cout << "move constructor \n";
	a.sz = 0; // make a the empty vector
	a.elem = nullptr;
}

Container<double>::~Container()
{
	cout << "destructor delete[] elem\n";
	delete[] elem;
}

template< > void Container<double>::copy(const Container<double>& arg) {
	for (int i = 0; i<arg.sz; ++i) elem[i] = arg.elem[i];
}


Container<double>& Container<double>::operator=(const Container<double>& a)
{
	cout << "operator = make this vector a copy of a \n";
	double* p = new double[a.sz]; // allocate new space
	for (int i = 0; i<a.sz; ++i) p[i] = a.elem[i];
	//copy(a.elem, a.elem + a.sz, p);
	cout << "now we can reset elem \n";
	delete[] elem; // deallocate old space
	cout << "now we can reset elem \n";
	elem = p; // now we can reset elem
	sz = a.sz;
	space = sz;
	return *this; // return a self-reference (see §17.10)
}

double& Container<double>::operator[](int n)
{ 
	return elem[n]; 
} // return element

double Container<double>::operator[](int n) const { // for const vectors
	return elem[n];
}

/*Container& Container::operator=(Container&& a) // move a to this vector
{
	cout << " move(operator) a to this vector \n";
	delete[] elem; // deallocate old space
	elem = a.elem; // copy a’s elem and sz
	sz = a.sz;
	a.elem = nullptr; // make a the empty vector
	a.sz = 0;
	return *this; // return a self-reference (see §17.10)
}*/

void Container<double>::set(int pos, double val) {
	elem[pos] = val;
}

void Container<double>::print() const {
	cout << "Container: ";
	for (int i = 0; i < sz; i++) {
		cout << elem[i] << " ";
	}
	cout << "\n";

}

void Container<double>::reserve(int newalloc)
{
	if (newalloc <= space) return; // never decrease allocation
	double* p = new double[newalloc]; // allocate new space
	for (int i = 0; i<sz; ++i) p[i] = elem[i]; // copy old elements
	delete[] elem; // deallocate old space
	elem = p;
	space = newalloc;
}

int Container<double>::capacity() const {	return space; }

void Container<double>::resize(int newsize)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
	if (newsize < capacity()) {
		throw myex;
	}
	reserve(newsize);
	for (int i = sz; i<newsize; ++i) elem[i] = 0; // initialize new elements
	sz = newsize;
}

void Container<double>::push_back(const double d)
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
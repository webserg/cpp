#include "main.h"
#include "Container.h"

void func3(vector<int>& v) {
	for_each(v.begin(), v.end(), [](int& i) { i++; });
}
void func0(vector<int>& v) {
	for_each(v.begin(), v.end(), [](int) {});
}
void printVector(vector<int>& v) {
	for_each(v.begin(), v.end(), [](int i) { cout << " " << i; });
}
void func5(std::vector<int>& v, const int& epsilon) {
	std::transform(v.begin(), v.end(), v.begin(),
		[epsilon](int d) -> int {
		return d + epsilon;
	});
}
void abssort(float* x, unsigned n) {
	std::sort(x, x + n,
		// Lambda expression begins
		[](float a, float b) {
		return (std::abs(a) < std::abs(b));
	} // end of lambda expression
	);
}
void useLambda() {
	cout << "start ";
	vector<int> v{ 1,2,3,4 };
	vector<int> d{ 1,2,3,4 };
	func3(v);
	printVector(v);
	cout << "\n func5 \n";
	func5(d, 1);
	printVector(d);
	cout << "\n";
}

Container<double> createContainer(const int i) {
	Container<double> v{ i };
	v.set(1, 99.0);
	v.print();
	return v;
}

Container<double>* make_vec() // make a filled vector
{
	Container<double>* p = new Container<double>; // we allocate on free store
	//&p.set(1, 11.0);								  // . . . fill the vector with data; this may throw an exception . . .
	return p;
}

void useContainer() {
	Container<double> v = createContainer(5);
	v.print();
	Container<double> v1{ 5 };
	v1.set(1, 999.0);
	v1.print();
	
	Container<double> v2{ v };
	v2.print();
	cout << "v3 -- \n";
	Container<double> v3{ 5 };
	v3 = v;
	v3.push_back(555);
	v3.print();
	v1 = std::move(v3);
	v1.print();
	cout << "makevec\n";
	Container<double>* con = make_vec();
	cout << "finish\n";
}
void useAccessOperatorContainer() {
	Container<double> v(10);
	double x = v[2]; // fine
	//v[3] = x; // error: v[3] is not an lvalue
	cout << "start --\n";
	for (int i = 0; i < v.size(); ++i) { // works, but still too ugly
		v[i] = i;
		cout << v[i] << "\n";
	}
}

void useArray() {

	char lac[20]; // local array; “lives” until the end of scope
	int lai[60];
	double lad[100]; // error: array size not a constant
	double ad[10];
	ad[5] = 99;
	double* p = &ad[5]; // point to ad[5]
	cout << "array 5 elem = " << *p << "\n";
	for (double* p = &ad[0]; p<&ad[10]; ++p) cout << *p << '\n';
				   // . . .
}
void useList() {
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = norse_gods->insertBefore(new Link{ "Odin" });

	norse_gods = norse_gods->insertBefore(new Link{ "Freia" });

	cout << "\n";
	norse_gods->print();
	cout << "\n";
	cout << norse_gods->succ->value;
	cout << "\n";
	norse_gods = norse_gods->addAfter(new Link{ "Me" });
	norse_gods->prev->print();
	cout << "\n";
	cout << "find " << norse_gods->prev->find("Me")->value;
	cout << "\n";
	norse_gods = norse_gods->erase();
	norse_gods->prev->print();
	cout << "\n";
}

struct X { // simple test class
	int val;
	void out(const string& s, int nv)
	{
		cerr << this << " -> " << s << " : " << val << " (" << nv << ")\n";
	}
	X() { out("X()", 0); val = 0; } // default constructor

	X(int v) { val = v; out("X(int)", v); }

	X(const X& x) { val = x.val; out("X(X&) ", x.val); } // copy constructor

	X& operator=(const X& a) // copy assignment
	{
		out("X::operator=()", a.val); val = a.val; return *this;
	}
	~X() { out("~X()", 0); } // destructor
};

X glob(2); // a global variable
X copy(X a) { return a; }
X copy2(X a) { X aa = a; return aa; }
X& ref_to(X& a) { return a; }
X* make(int i) { X a(i); return new X(a); }
struct XX { X a; X b; };

int gai[100];

void useConstructor() {
	X loc{ 4 }; // local variable
	X loc2{ loc }; // copy construction
	loc = X{ 5 }; // copy assignment
	//loc2 = copy(loc); // call by value and return
	//loc2 = copy2(loc);
	//X loc3{ 6 };
	//X& r = ref_to(loc); // call by reference and return
	//delete make(7);
	//delete make(8);
	//vector<X> v(4); // default values
	//XX loc4;
	//X* p = new X{ 9 }; // an X on the free store
	//delete p;
	//X* pp = new X[5]; // an array of Xs on the free store
	//delete[] pp;
}

vector<int> gv{1,2,4,8,16};

void f(vector<int> v) {
	vector<int> lv{gv};
	for (int i = 0; i < lv.size(); i++) {
		cout << lv[i] << "\n";
	}

	cout << "==============\n";

	vector<int> lv2{ v };
	for (int i = 0; i < lv2.size(); i++) {
		cout << lv2[i] << "\n";
	}
}

int main() {
	//useLambda();
	useContainer();
	//useList();
	//useConstructor();
	//useAccessOperatorContainer();
	//useArray();
	//f(gv);
	//vector<int> vv(10);
	//for (int i = 0; i < vv.size(); i++) {
	//	if(i==0) vv[i] = 1;
	//	else vv[i] = i * vv[i - 1];
	//}
	//cout << "vvvv";
	//f(vv);
	keep_window_open();
}
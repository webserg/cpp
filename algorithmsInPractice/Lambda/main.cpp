#include "main.h"
#include "Container.h"
#include <set>
#include <thread>
#include <cassert>

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
	for (double* p = &ad[0]; p < &ad[10]; ++p) cout << *p << '\n';
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
	X() { out("default constructor X()", 0); val = 0; } // default constructor

	X(int v) { val = v; out("constructor X(int)", v); }

	X(const X& x) { val = x.val; out("copy constructor X(X&) ", x.val); } // copy constructor

	X& operator=(const X& a) // copy assignment
	{
		out("copy assignment X::operator=()", a.val); val = a.val; return *this;
	}
	~X() { out("destructor ~X()", 0); } // destructor
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

vector<int> gv{ 1,2,4,8,16 };

void f(vector<int> v) {
	vector<int> lv{ gv };
	for (int i = 0; i < lv.size(); i++) {
		cout << lv[i] << "\n";
	}

	cout << "==============\n";

	vector<int> lv2{ v };
	for (int i = 0; i < lv2.size(); i++) {
		cout << lv2[i] << "\n";
	}
}

void suspicious1(int s, int x)
{
	int* p = new int[s]; // acquire memory
						 // . . .
	if (x) return;
	// . . .
	delete[] p; // release memory but can't be achived so memory leak
}

void suspicious2(int s, int x) // messy code
{
	int* p = new int[s]; // acquire memory
	vector<int> v;
	// . . .
	try {
		if (x) p[x] = v.at(x);
		// . . .
	}
	catch (exception) { // catch every exception
		delete[] p; // release memory
		throw; // re-throw the exception
	}
	// . . .
	delete[] p; // release memory
}

void f(vector<int>& v, int s)
{
	vector<int> p(s);
	vector<int> q(s);
	//acquired by a constructor and released by the matching destructor
}

vector<int>* make_vec1() // make a filled vector
{
	vector<int>* p = new vector<int>; // we allocate on free store
									  // . . . fill the vector with data; this may throw an exception . . .
	return p;
}

vector<int>* make_vec2() // make a filled vector
{
	vector<int>* p = new vector<int>; // we allocate on free store
	try {
		// fill the vector with data; this may throw an exception
		return p;
	}
	catch (exception) {
		delete p; // do our local cleanup
		throw; // re-throw to allow our caller to deal with the fact
			   // that make_vec() couldn’t do what was
			   // required of it
	}
}

std::unique_ptr<vector<int>> make_vec3() // make a filled vector using “smart” pointer
{
	unique_ptr<vector<int>> p{ new vector<int> }; // allocate on free store
												  // . . . fill the vector with data; this may throw an exception . . .
	return p;
}
//The move solution generalizes to all containers and further still to all resource handles.
vector<int> make_vec4() // make a filled vector
{
	vector<int> res;
	// . . . fill the vector with data; this may throw an exception . . .
	return res; // the move constructor efficiently transfers ownership
}

struct Foo
{
	int _i;
	Foo(int i) :_i(i) { std::cout << "Foo::Foo " << _i << "\n"; }
	~Foo() { std::cout << "Foo::~Foo " << _i << "\n"; }
	void bar() { std::cout << "Foo::bar\n"; }
};

unique_ptr<Foo> f(Foo &)
{
	std::cout << "f(const Foo&)\n";
	//foo->bar();
	unique_ptr<Foo> p1(new Foo(1));
	return p1;
}

void useSmartPointer()
{

	unique_ptr<Foo> p1(new Foo(0));  // p1 owns Foo
	if (p1) p1->bar();

	unique_ptr<Foo> p3 = f(*p1);
	cout << "finish\n";
}

void useMaps() {
	map<string, string> dictionary;
	typedef map<int, string> MyMap;
	MyMap map;
	dictionary["sea"] = "large body of water"; // insert or assign to element
	cout << "map:\n";
	cout << dictionary["sea"]; // read value
	cout << "\n";
	int key = 1;
	string value = "1";
	std::pair<MyMap::iterator, bool> res = map.insert(make_pair(key, value));
	if (!res.second) {
		cout << "key " << key << " already exists "
			<< " with value " << (res.first)->second << endl;
	}
	else {
		cout << "created key " << key << " with value " << value << endl;
	}
	cout << map[1] << "\n";
}

class Employee {
public:

	Employee(const string& fname, const string& sname) : first_name{ fname }, family_name{ sname } {
	}
	virtual void print() const;
	string full_name() const { return first_name + ' ' + family_name; }
	virtual ~Employee() {}
	// ...
private:
	string first_name, family_name;

	// ...
};
class Manager : public Employee {
public:
	using Employee::Employee;
	//Manager(const string& fname, const string& sname, int lvl) : level{lvl} {
	//}
	void print() const override;
private:
	int level{ 0 };
	// ...
};
class Message
{
	int id;
public:
	Message(int _id) :id{ _id }
	{

	}
	~Message() {}
	void print() const
	{
		cout << id << "\n";
	}
	bool operator>(const Message& rhs) const;
	bool operator<(const Message& rhs) const;
};

bool Message::operator>(const Message& rhs) const {
	return (id > rhs.id);
}
bool Message::operator<(const Message& rhs) const {
	return (id < rhs.id);
}

void Employee::print() const
{
	cout << "Employee :: name is " << family_name << '\n';
}

void Manager::print() const
{
	cout << "name is " << full_name() << '\n';
	Employee::print(); // print Employee information
}

void print_list(const list<Employee*>& s)
{
	for (auto x : s)
		x->print();
}

typedef map<int, Employee*> EmployeeMap;

Employee* getById(int id, EmployeeMap map) {
	EmployeeMap::const_iterator it;
	it = map.find(id);
	if (it != map.end())
	{
		return it->second;

	}
	else return nullptr;
}

void useEmployee() {
	Employee e{ "Sergiy","Doroshenko" };
	Manager m{ "Ss","Manager" };
	print_list({ &e,&m });

	EmployeeMap emap;
	emap[0] = &e;
	emap[1] = &m;
	Employee* empl = getById(1, emap);
	cout << empl->full_name() << "\n";
}
void useManager(Manager* m, Message& message)
{
	m->print();
	message.print();
	Message m2{ 2 };
	message = m2;
	message.print();
	Manager mm{ "Ss","Manager" };
	m = &mm;
	m->print();
}

void useRef()
{
	Manager m{ "Ss","Manager" };
	Message m1{ 1 };
	useManager(&m, m1);

}

void useSet()
{
	Message m1{ 1 };
	Message m2{ 2 };
	Message m3{ 3 };
	//set<Message, greater<const Message&>> pqueue_messages;
	set<Message> pqueue_messages;
	pqueue_messages.insert(m1);
	pqueue_messages.insert(m2);
	pqueue_messages.insert(m3);
	for (auto i : pqueue_messages)
		i.print();
}


struct BankAccount
{
	int balance = 1;
	BankAccount()
	{

	}
	explicit BankAccount(int balance)
		: balance(balance)
	{
	}
};


class Empty {
public:
	Empty(string _id) :id(_id) {  } // default constructor		
	Empty(const Empty& rhs) :id(rhs.id) {} // copy constructor
										   /*In many cases, this is sufficient. However, there are certain
										   circumstances where the member-wise copy version is not good enough.
										   By far, the most common reason the default copy constructor is not
										   sufficient is because the object contains raw pointers and you need
										   to take a "deep" copy of the pointer.*/
	~Empty() {  } // destructor — see below
				  // for whether it's virtual
	Empty& operator=(const Empty& rhs) {
		id = rhs.id;
		return *this;
	} // copy assignment operator
	string print() { return id; }
private:
	string id;
};

void third_test()
{

	Empty e1("1"); // default constructor;
				   // destructor
	Empty e2(e1); // copy constructor
	e2 = e1; // copy assignment operator
	assert(e2.print() == "1");

}

int useFilesWrite() {
	char first_name[30], last_name[30]; int age;
	char file_name[20];
	// Collect the data.
	cout << "Enter First Name: "; cin >> first_name;
	cout << "Enter Last Name: "; cin >> last_name;
	cout << "Enter Age: "; cin >> age;
	cout << endl << "Enter the name of the file: "; cin >> file_name;

	// Create an ofstream called People, open the stream for output.
	ofstream People(file_name, ios::out);
	// Write the output to the stream.
	People << first_name << endl << last_name << endl << age << endl;
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
int useFilesRead() {
	string line;
	ifstream People("ttt.txt");
	if (People.is_open())
	{
		while (getline(People, line))
		{
			cout << line << '\n';
		}
		People.close();
	}
	return 0;
}
// Improperly declared function:  parameter should be const reference:
void print_me_bad(std::string& s) {
	std::cout << s << std::endl;
}

// Properly declared function: function has no intent to modify s:
void print_me_good(const std::string& s) {
	std::cout << s << std::endl;
}

void constCorrectness()
{
	std::string hello("Hello");
	/*
	When passing parameters by reference to functions or constructors, be very
	careful about const correctness. Pass by non-const reference ONLY if
	the function will modify the parameter and it is the intent to change
	the caller's copy of the data, otherwise pass by const reference.

	Why is this so important? There is a small clause in the C++ standard
	that says that non-const references cannot bind to temporary objects.
	A temporary object is an instance of an object that does not have a
	variable name
	*/
	print_me_bad(hello);  // Compiles ok; hello is not a temporary
	print_me_bad(std::string("World"));  // Compile error; temporary object
										 //print_me_bad("!"); // Compile error; compiler wants to construct temporary
										 // std::string from const char*

	print_me_good(hello); // Compiles ok
	print_me_good(std::string("World")); // Compiles ok
	print_me_good("!"); // Compiles ok 
}

int add(int i, int j) { return i + j; }


vector<X> fillVector()
{
	auto v = vector<X>(5);
	return v;
}

void printVector(const vector<X> v)
{
	for(auto& x:v)
	{
		cout << "x = " << x.val << "\n";
	}
}

void userVector()
{
	printVector(fillVector());
	//auto v =  fillVector();
}

int main() 
{

	useRef();
	//useSet();
	//using namespace chrono;
	//milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	//cout << ms.count() << "\n";
	//useEmployee();
	//useMaps();
	//useSmartPointer();
	//useLambda();
	//useContainer();
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
	//argc = 1;
	//argv[0] = "-r xml";
	//int result = Catch::Session().run(argc, argv);
	//useFilesWrite();
	//useFilesRead();
	//constCorrectness();
	userVector();

	keep_window_open();

}
/*
[4]
Modify class Link from §15.7 to be a template with the type of value as the template argu-
ment. Then redo exercise 13 from Chapter 15 with Link<God>.
*/

import PPP;
using namespace std;

struct God
{
	string name;
	string mythology;
	string vehicle;
	string weapon;
	auto operator<=>(const God&)const = default;
};
template <typename T>
struct Link {
	Link(const T& v, Link<T>* p = nullptr, Link<T>* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } {
	}
	T value;
	Link<T>* prev;
	Link<T>* succ;
	~Link();//forward
};
template <typename T>
Link<T>::~Link()
{
	//cout << "deleting " << value.name << '\n';
	if (succ)delete succ;
}

auto add(auto p, auto n)
{
	if (n == nullptr)
		return p;

	n->succ = move(p->succ);
	if (p->succ)p->succ->prev = n;

	p->succ = n;
	n->prev = p;
	return n;
}
void print_all(auto p)
{
	cout << "{ ";
	while (p)
	{
		cout << p->value.name << ' '
			<< p->value.mythology << ' '
			<< p->value.vehicle << ' '
			<< p->value.weapon << ' ';
		if (p = p->succ)
			cout << ",\n";
	}
	cout << " }";
}


void test_()
{
	Link<God>* norse_gods = new Link<God>( {"Thor"} );
	add(norse_gods, new Link<God>{ {"Odin"} });
	add(norse_gods, new Link<God>{ {"Zeus" } });
	add(norse_gods, new Link<God>{ {"Freja"} });

	print_all(norse_gods);
	cout << '\n';
	delete norse_gods;
}
int main()
try {
	test_();

	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
	return 1;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 2;
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 3;
}
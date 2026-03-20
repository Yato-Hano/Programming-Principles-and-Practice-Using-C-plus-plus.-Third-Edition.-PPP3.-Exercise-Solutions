/*
[14]
Could the ‘‘list of gods’’ example from §15.7 have been written using a singly-linked list;
that is, could we have left the prev member out of Link? Why might we want to do that? For
what kind of examples would it make sense to use a singly-linked list? Re-implement that
example using only a singly-linked list.
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
struct Link {
	Link(const God& v,  Link* s = nullptr)
		: value{ v }, succ{ s } {
	}
	God value;
	Link* succ;
};

Link* add(Link* p, Link* n)
{
	if (n == nullptr)
		return p;
	if (p == nullptr)
		return n;

	n->succ = p->succ;
	p->succ = n;
	return n;
}
Link* find(Link* p, const God& s)
// find s in list; return nullptr for ‘‘not found’’
{
	while (p) {
		if (p->value == s)
			return p;
		p = p->succ;
	}
	return nullptr;
}
Link* advance(Link* p, int n)
// move n positions in list; return nullptr for ‘‘not found’’
// positive n moves forward, negative backward
{
	if (p == nullptr)
		return nullptr;
	while (0 < n)
	{
		--n;
		if (p->succ)
			p = p->succ;
		else
			return nullptr;
	}
	

	return p;
}
void print_all(Link* p)
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

void delete_all(Link* p)
{
	Link* p2 = nullptr;
	while (p)
	{
		p2 = p->succ;
		delete p;
		p = p2;
	}
}
int main()
try {
	Link* norse_gods = new Link{ {"Thor"} };
	add(norse_gods, new Link{ {"Odin"} });
	add(norse_gods, new Link{ God{"Zeus" } });
	add(norse_gods, new Link{ {"Freja"} });
	add(norse_gods, new Link{ {"Odin2" } });
	add(norse_gods, new Link{ {"Odin3"} });

	print_all(norse_gods);
	cout << '\n';
	delete_all(norse_gods);

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
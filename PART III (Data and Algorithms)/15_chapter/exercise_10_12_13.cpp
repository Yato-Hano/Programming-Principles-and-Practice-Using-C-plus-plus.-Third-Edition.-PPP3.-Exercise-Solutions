/*
[10]
Complete the ‘‘list of gods’’ example from §15.7 and run it.
[12]
Modify the Link class from §15.7 to hold a value of a struct God. struct God should have
members of type string: name, mythology, vehicle, and weapon. For example, God{"Zeus",
"Greek", "", "lightning"} and God{"Odin", "Norse", "Eight−legged flying horse called Sleipner",
"Spear called Gungnir"}. Write a print_all() function that lists gods with their attributes one per
line. Add a member function add_ordered() that places its new element in its correct lexico-
graphical position. Using the Links with the values of type God, make a list of gods from
three mythologies; then move the elements (gods) from that list to three lexicographically
ordered lists – one for each mythology.
[13]
Modify the ‘‘list of gods’’ example from §15.7 not to leak memory.
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
	Link(const God& v, Link* p = nullptr, Link* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } {
	}
	God value;
	Link* add_ordered(Link* new_node);
	Link* prev;
	Link* succ;
};
Link* insert(Link* p, Link* n)
// inser t n before p; return n
{
	if (n == nullptr)
		return p;
	if (p == nullptr)
		return n;
	n-> succ = p;
	if (p-> prev)
		p-> prev-> succ = n;
	n-> prev = p-> prev;
	p-> prev = n;
	return n;
}


Link* add(Link* p, Link* n)
{
	if (n == nullptr)
		return p;
	if (p == nullptr)
		return n;

	n->succ = p->succ;
	if (p->succ)p->succ->prev = n;

	p->succ = n;
	n->prev = p;
	return n;
}
Link* Link::add_ordered(Link* new_node)
{
	if (new_node == nullptr)
		return this;
	Link* current = this;
	while (current->succ && current->value < new_node->value) {
		current = current->succ;
	}
	cout << "current " << current->value.name << ", new_node " << new_node->value.name << '\n';

	if(current->value < new_node->value)	
		return add(current, new_node);// no current->succ 
	else
		return insert(current, new_node); 
}

Link* erase(Link* p)
// remove *p from list; return p’s successor
{
	if (p == nullptr)
		return nullptr;
	if (p-> succ)
		p-> succ-> prev = p-> prev;
	if (p-> prev)
		p-> prev-> succ = p-> succ;
	return p-> succ;
}
Link*find(Link* p, const God& s)
// find s in list; return nullptr for ‘‘not found’’
{
	while (p) {
		if (p-> value == s)
			return p;
		p = p-> succ;
	}
	return nullptr;
}
Link* advance(Link* p, int n)
// move n positions in list; return nullptr for ‘‘not found’’
// positive n moves forward, negative backward
{
	if (p == nullptr)
		return nullptr;
	while (0 < n) {
		--n;
		if (p-> succ)
			p = p-> succ;
		else
			return nullptr;
	}
	while (n < 0) {
		++n;
		if (p-> prev)
			p = p-> prev;
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
		cout << p-> value.name <<' '
			<< p->value.mythology << ' '
			<< p->value.vehicle << ' '
			<< p->value.weapon<< ' ';
		if (p = p-> succ)
			cout << ",\n";
	}
	cout << " }";
}

void delete_all(Link* p)
{
	Link* p2=nullptr;
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
	 
	Link* greek_gods = new Link{ {"Hera"} };
	greek_gods = insert(greek_gods, new Link{ {"Athena"} });
	greek_gods = insert(greek_gods, new Link{ {"Mars"} });
	greek_gods = insert(greek_gods, new Link{ {"Poseidon"} });

	Link* ordered_list = new Link{ {"1"} };
	ordered_list->add_ordered(new Link{ {"3"} });
	ordered_list->add_ordered(new Link{ {"2"} });
	ordered_list->add_ordered(new Link{ {"4"} });
	cout << "Ordered:\n";
	print_all(ordered_list);
	cout << '\n';
	//print_all(norse_gods);
	cout << '\n';
	//print_all(greek_gods);
	cout << '\n';
	delete_all(greek_gods);
	delete_all(norse_gods);
	delete_all(ordered_list);
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



/*
list<string> norse_gods;
	norse_gods.insert(norse_gods.begin(), "Thor");
	norse_gods.insert(norse_gods.begin(), "Odin");
	norse_gods.insert(norse_gods.begin(), "Freja");
	for (string& s : norse_gods)
	{
		cout << s << ' ';
	}
	cout << '\n';
	list<string> greek_gods;
	greek_gods.insert(greek_gods.begin(), "Hera");
	greek_gods.insert(greek_gods.begin(), "Athena");
	greek_gods.insert(greek_gods.begin(), "Ares");
	greek_gods.insert(greek_gods.begin(), "Poseidon");
	greek_gods.insert(greek_gods.begin(), "Zeus");
	for (string& s : greek_gods)
	{
		cout << s << ' ';
	}
	cout << '\n';
*/
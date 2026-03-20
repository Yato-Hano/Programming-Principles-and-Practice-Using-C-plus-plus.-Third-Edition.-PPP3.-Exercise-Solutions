/*

*/

import PPP;
using namespace std;

struct Fruit {
	string name;
	int count;
	double unit_price;
	//Date last_sale_date;
};
struct Fruit_comparison {
	
	bool operator()(const Fruit* a, const Fruit* b) const
	{
		return a->name < b->name;
	}
};
ostream& operator<<(ostream& os, const Fruit& f)
{

	return os <<"{ " << f.name << ' ' << f.count << ' ' << f.unit_price << " }";
}

int main()
try {
	Fruit f1{ "quince",5 };
	Fruit f2{ "apple",200,0.37 };
	set<Fruit*, Fruit_comparison> inventory;
	inventory.insert(&f1 );
	inventory.insert( &f2);

	for (const auto& x : inventory)
		cout << *x << '\n';

	system("pause");
	return 0;
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
/*

*/

import PPP;
using namespace std;

struct Item
{
	string name;
	int iid;
	double value;
};
ostream& operator<<(ostream& os, const Item& v)
{
	return os << "{ " << v.name << " " << v.iid << " " << v.value << " }";
}
istream& operator>>(istream& is, Item& v)
//{name iid value}
{
	char ch{};
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	v = {};
	
	is >> v.name>>v.iid>>v.value>>ch;

	if(!is)
		throw exception{ "Bad Item" };

	if (ch == '}')
		return is;
	else 
		throw exception{ "Bad Item termination" };
}
void read_to_msi(map<string, int>& msi)
{
	string s;
	int i{};
	char ch1{}, ch2{};
	while (cin >> ch1 && ch1=='{'&& cin >> s >> i)
	{
		msi[s] = i;
		if (cin >> ch2)
			if (ch2 != '}')break;
	}
	
}
template<class T,class O>
void copy_msi_to_mis(const map<T, O>& msi, map<O, T>& mis)
{
	for (const auto& [t, o] : msi)mis.try_emplace(o,t);
}
int msi_sum(const map<string, int>& msi)
{
	int sum{ 0 };
	for (const auto& s : msi)sum += s.second;
	return sum;
}
int main()
try {

	map<string, int>msi;
	msi["v"] = 3;
	msi["c"] = 15;
	msi["a"] = 2;
	msi["lecture"] = 21;
	msi["lecture2"] = 212;
	cout << "msi rading: ";
	read_to_msi(msi);

	//msi.erase("lecture");
	//msi.erase(msi.begin());
	for (const auto& [st, val] : msi)cout << st << ' ' << val << '\n';
	cout << "msi sum: " << msi_sum(msi) << '\n';
	map<int, string>mis;
	cout << "mis:\n";
	copy_msi_to_mis(msi,mis);
	for (const auto& [st, val] : mis)cout << st << ' ' << val << '\n';



	system("pause");
	ifstream is{ "data.txt"};
	ofstream os{ "output.txt"};
	//vector<Item> vi{ istream_iterator<Item>{is},istream_iterator<Item>{} };
	list<Item> vi{ istream_iterator<Item>{is},istream_iterator<Item>{}};
	//ranges::sort(vi, [](const Item& i1, const Item& i2) {return i1.iid < i2.iid; });
	//ranges::sort(vi, [](const Item& i1, const Item& i2) {return i1.name < i2.name; });
	vi.insert(vi.end(), Item{ "horse shoe",99,12.34 });
	vi.insert(vi.end(), Item{ "Canon S400", 9988,499.95 });
	
	if (auto iter = find_if(vi.begin(), vi.end(), [](const Item& i) {return i.name == "horse shoe"; });
		iter != vi.end())	
	{		vi.erase(iter);	}
	if (auto iter = find_if(vi.begin(), vi.end(), [](const Item& i) {return i.iid == 5; });
		iter != vi.end())
	{
		vi.erase(iter);
	}
	vi.sort( [](const Item& i1, const Item& i2) {return i1.value < i2.value; });
	//ranges::sort(vi, [](const Item& i1, const Item& i2) {return i1.value < i2.value; });
	ranges::copy(vi, ostream_iterator<Item>{os, "\n"});
	//copy(vi.rbegin(), vi.rend(), ostream_iterator<Item>{os, "\n"});

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
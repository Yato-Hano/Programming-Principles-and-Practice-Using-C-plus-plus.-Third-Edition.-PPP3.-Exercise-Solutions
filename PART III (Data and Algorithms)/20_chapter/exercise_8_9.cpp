/*
[8]
Read a sequence of (name,height) pairs into a map. Names should be represented as strings
and heights by ints. Output the pairs lexicographically sorted by name. Print a name : height
per line.
[9]
Output the pairs from the previous exercise sorted by height in decreasing order (tallest first).
*/

import PPP;
using namespace std;

istream& operator>>(istream& is,pair<string, int>& v)
//{name,height}
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
	char i = 0;
	while ( is.get(ch) && ch !=',' )
		v.first += ch;

	if (ch != ',' || !(is >> v.second))
		throw exception{ "Bad pair" };
	is >> ch;
	if (ch == '}')
		return is;
	else
		throw exception{ "Bad pair termination" };
}

int main()
try {
	map<string, int> names;
	
	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "No file" };
	
	for (pair<string, int> s{}; ifs >> s; )
		names.emplace(s);

	cout << "sorted by names(lowest first):\n";
	for (const auto& [ name,height] : names)
		cout << name  << ": " << height << '\n';

	vector<pair<int, const string*>> heights;
	heights.reserve(names.size());
	for (const auto& [name, height] : names)
		heights.push_back(pair<int, const string*>{height, & name});
	
	ranges::sort(heights,
		[](const auto& one, const auto& other)
		{return one.first > other.first; });
	
	cout << "sorted by heights(tallest first):\n";
	for (const auto& [height, name] : heights)
		cout << height << ": " << *name << '\n';

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
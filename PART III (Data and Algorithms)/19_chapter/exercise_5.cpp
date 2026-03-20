/*
[5]
Define an input and an output operator (>> and <<) for vector.
*/

import PPP;
using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
//{val,val}
{
	os << "{ ";
	for (size_t i = 0; i < v.size(); i++)
	{
		os << v[i];
		if ((1 + i) < v.size())	os << ',';
		os << ' ';
	}
	os << '}';
	return os;
}
template<typename T>
istream& operator>>(istream& is, vector<T>& v)
//{val,val}
{
	char ch{};
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	v.clear();
	for (T val{}; is >> val; )
	{
		v.push_back(val);
		is >> ch;
		if (ch != ',')break;
	}
	if (ch == '}')
		return is;
	else throw exception{ "Bad vector termination" };
}


int main()
try {
	vector<double> v(10, 20);
	cin >> v;
	cout << v << '\n';
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
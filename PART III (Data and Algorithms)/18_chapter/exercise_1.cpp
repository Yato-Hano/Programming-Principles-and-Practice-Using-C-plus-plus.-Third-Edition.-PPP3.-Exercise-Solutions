/*
[1]
Write a template function add() that adds the elements of one vector<T> to the elements of
another; for example, add(v1,v2) should do v1[i]+=v2[i] for each element of v1.
*/

import PPP;
using namespace std;

template<typename T >
void add(vector<T>& v1, const vector<T>& v2)
{
	if (v1.size() < v2.size())return;
	for (size_t i = 0; i < v1.size(); i++)
		if(i < v2.size())
			v1[i] += v2[i];
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
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
int main()
try {
	vector<int>v1{ 0,1,2,3 };
	vector<int>v2{ 0,1,2,3,5 };

	add(v1, v2);
	cout << v1 << '\n';

	v1.push_back(5);
	add(v1, v2);
	cout << v1<<'\n';

	v1.push_back(6);
	add(v1, v2);
	cout << v1 << '\n';

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
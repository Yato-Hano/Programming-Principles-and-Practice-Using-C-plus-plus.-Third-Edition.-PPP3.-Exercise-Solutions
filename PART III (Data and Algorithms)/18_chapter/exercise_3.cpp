/*
[3]
Write a template class Pair that can hold a pair of values of any type. Use this to imple-
ment a simple symbol table like the one we used in the calculator (§6.8).
*/

import PPP;
using namespace std;

template<typename T, typename U>
class Pair {
public:
	T first;
	U second;
};

class Symbol_table {
public:
	vector<Pair<string,double>> names;
	double assign(string name); // name = expression()
	double declare(); // name = expression()
	double get(string s);
	void set(string s, double d); // set variable
	bool is_declared(string s);
};

int main()
try {
	Pair<string, double> pr{"test",13.4};

	cout << pr.first << ' ' << pr.second << '\n';

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
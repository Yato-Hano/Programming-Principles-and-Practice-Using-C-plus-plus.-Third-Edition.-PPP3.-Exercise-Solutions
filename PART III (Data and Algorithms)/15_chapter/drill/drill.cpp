/*

*/

import PPP;
using namespace std;

void print_array(ostream&os,int*a,int n)
{
	for (size_t i = 0; i < n; i++)
	{
		os << a[i] << '\n';
	}
}
void print_vector(ostream& os, vector<int> a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		os << a[i] << '\n';
	}
}
int main()
try {
	constexpr int max = 10;
	int* p2 = new int[max];
	for (size_t i = 0; i < max; i++)
	{
		p2[i] = i + 1;
	}
	
	int* p1 = new int[max];
	for (size_t i = 0; i < max; i++)
	{
		p1[i] = p2[i];
	}
	print_array(cout, p2, max);
	print_array(cout, p1, max);
	delete[]p2;
	delete[]p1;
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
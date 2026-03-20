/*
[7]
Find the lexicographical last string in an unsorted vector<string>.
*/

import PPP;
using namespace std;

int main()
try {
	vector<string> v{ "c","a","b" };
	cout << *std::ranges::max_element(v)<<'\n';
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
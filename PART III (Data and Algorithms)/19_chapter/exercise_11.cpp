/*
[11]
Given a list<int> as a (by-reference) parameter, make a vector<double> and copy the elements
of the list into it. Verify that the copy was complete and correct. Then print the elements
sorted in order of increasing value.
*/

import PPP;
using namespace std;

void test_copy_and_sort(const list<int>& l)
{
	vector<int> v{ l.begin(),l.end() };
	
	if (std::ranges::equal(l, v))
		cout << "Copy succeess.\n";
	else
		cout << "Copy not succeess.\n";

	std::ranges::sort(v);
	for (int n : v) cout << n << ' ';
	cout << '\n';
}

int main()
try {
	list<int>l{ 1,3,2,5 };
	test_copy_and_sort(l);
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
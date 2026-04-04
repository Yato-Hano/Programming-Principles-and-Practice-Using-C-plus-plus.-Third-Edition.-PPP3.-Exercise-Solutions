/*
[16]
Write a program that produces the sum of all the numbers in a file of whitespace-separated
integers.
*/

import PPP;
using namespace std;

int main()
try {
	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "No file" };

	int sum{};
	for (int val{ 0 }; ifs >> val;) sum += val;

	if (!ifs.eof())  throw exception{ "That was not an integer number" };

	cout<< "Sum is " << sum << '\n';

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
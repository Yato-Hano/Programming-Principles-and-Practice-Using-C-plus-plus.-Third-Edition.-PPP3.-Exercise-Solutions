/*
[14]
Write a program that reads a file of whitespace-separated numbers and outputs a file of num-
bers using scientific format and precision 8 in four fields of 20 characters per line.
*/

import PPP;
using namespace std;

int main()
try {
	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "No file" };
	vector<double> numbers;
	for (double val{ 0 }; ifs >> val;)
		numbers.push_back(val);
	if(!ifs.eof())  throw exception{ "That was not a number" };

	cout << left<<setprecision(8);
	for (size_t i = 0; i < numbers.size(); i++)
	{
		cout << setw(20) << numbers[i];
		if ((i % 3) == 0&&i!=0)cout << '\n';
	}

	cout << '\n';
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
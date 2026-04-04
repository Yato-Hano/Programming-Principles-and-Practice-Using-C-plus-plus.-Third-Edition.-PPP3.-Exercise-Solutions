/*
[15] 
Write a program to read a file of whitespace-separated numbers and output them in order
(lowest value first), one value per line. Write a value only once, and if it occurs more than
once write the count of its occurrences on its line. For example, 7 5 5 7 3 117 5 should give
3
5	3
7	2
117
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
	if (!ifs.eof())  throw exception{ "That was not a number" };
	sort(numbers.begin(), numbers.end());

	int count{ 1 };
	for (size_t i = 1; i < numbers.size(); i++)
	{
		if (numbers [i-1] == numbers[i])
			count++;
		else 
		{ 
			cout << numbers[i-1] << '\t';
			if(count!=1)
				cout << count;
			cout << '\n';
			count = 1;
		}
	}
	cout << numbers[numbers.size()-1] << '\t';
		if (count != 1)
			cout << count;
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


/*
for (double d: numbers)
	{
		if (prev == d) count++;
		else {
			if(not_a_number!=prev)
				cout << prev << '\t';
			if(count!=1)
				cout << count;
			cout << '\n';
			count = 1;
			prev = d;
		}
	}
*/
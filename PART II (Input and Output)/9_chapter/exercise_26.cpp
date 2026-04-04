/*
[26]
Write a program that produces the sum of all the whitespace-separated integers in a text file.
For example, bears: 17 elephants 9 end should output 26.
*/

import PPP;
using namespace std;

int main()
try {
	ifstream ifs{ "t2.txt" };
	if (!ifs) throw exception{ "No file" };
	int sum{}, number{ 0 };
	for (char ch{}; ifs;)
	{
		ifs.get(ch);
		if (iswspace(ch)) {
			ifs.get(ch);
			if (iswdigit(ch)) {
				ifs.unget();
				ifs >> number;
				ifs.get(ch);
				if (iswspace(ch)) {
					sum += number;
				}
			}
		}


	}


	if (!ifs.eof())  throw exception{ "Bad reading" };
	ifs.close();

	cout << sum << '\n';


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
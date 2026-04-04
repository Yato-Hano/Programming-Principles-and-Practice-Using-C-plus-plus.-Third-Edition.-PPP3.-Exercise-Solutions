/*
[11]
Reverse the order of characters in a text file. For example, asdfghjkl becomes lkjhgfdsa.
Warning: There is no really good, portable, and efficient way of reading a file backward.
*/

import PPP;
using namespace std;

int main()
try {
	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "No file" };

	string text{
		istreambuf_iterator<char>(ifs),
		istreambuf_iterator<char>()
	};
	ifs.close();

	ofstream ofs{ "t.txt" };
	if (!ofs) throw exception{ "No file" };

	reverse(text.begin(), text.end());

	ofs << text;
	ofs.close();

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
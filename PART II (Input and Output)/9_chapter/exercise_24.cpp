/*
[23]
Write a program that accepts two file names and produces a new file that is the contents of
the first file followed by the contents of the second; that is, the program concatenates the two
files.
*/

import PPP;
using namespace std;

int main()
try {
	ifstream ifs1{ "t1.txt" };
	if (!ifs1) throw exception{ "No file" };
	ifstream ifs2{ "t2.txt" };
	if (!ifs1) throw exception{ "No file" };

	vector<string> words;
	for (string s; ifs1 >> s;)
		words.push_back(s);
	for (string s; ifs2 >> s;)
		words.push_back(s);

	sort(words.begin(), words.end());

	ofstream ofs{ "t_out.txt" };
	if (!ofs) throw exception{ "No file" };
	for (string s : words)ofs << s << ' ';
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
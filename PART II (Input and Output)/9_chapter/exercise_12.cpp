/*
[12]
Reverse the order of words (defined as whitespace-separated strings) in a file. For example,
Norwegian Blue parrot becomes parrot Blue Norwegian. Assume that all the strings from the
file will fit into memory at once.
*/

import PPP;
using namespace std;

int main()
try {

	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "No file" };

	vector<string> words;

	for (string s; ifs >> s;)words.push_back(s);
	ifs.close();
	reverse(words.begin(), words.end());

	ofstream ofs{ "t.txt" };
	if (!ofs) throw exception{ "No file" };
	for (const string& s : words)ofs << s << ' ';
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
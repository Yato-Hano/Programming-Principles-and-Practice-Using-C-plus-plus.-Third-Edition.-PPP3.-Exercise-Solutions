/*
[10]
Read the lines from a file of text and output the unique lines (once only). Hint: read the lines
into a map and output a line only if it hasn’t been seen before. This is the AWK program
(!a[$0]++).
*/

import PPP;
using namespace std;

int main()
try {
	ifstream ifs{ "data.txt" };
	if (!ifs) throw exception{ "No file" };

	set<string> lines;

	for (string line; getline(ifs, line);)
		lines.insert(line);

	cout << "Unique lines:\n";
	for (const string &line : lines) cout << line << '\n';

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
/*
[1]
Write a program that reads a text file and converts its input to all lowercase, producing a new
file.
*/

import PPP;
using namespace std;

int main()
try {
	string text;
	ifstream ifs{ "text_file.txt" };
	if (!ifs) throw string{ "Can't open file 1" };

	for (char i = 0; ifs.get(i); )
		text += tolower(i);
	ifs.close();

	ofstream ofs{ "text_file_lower.txt" };
	if (!ofs) throw string{ "Can't open file 2" };

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
/*
[3]
Write a program that removes all vowels from a file (‘‘disemvowels’’). For example, Once
upon a time! becomes nc pn tm!. Surprisingly often, the result is still readable; try it on your
friends.
*/

import PPP;
using namespace std;

bool is_vowel(char c)
{
	switch (tolower(c))
	{
	case 'a':	case 'e':
	case 'i':	case 'o':
	case 'u':
		return true;
	default:
		return false;
	}
}


int main()
try {
	ifstream ifs{ "disemvowels.txt" };
	if (!ifs) throw string{ "Can't open file 1" };

	string disemvowels_text;

	for (char ch{}; ifs.get(ch);)
		if (!is_vowel(ch)) disemvowels_text += ch;
	ifs.close();

	ofstream ofs{ "disemvowels.txt",ios::app };
	if (!ofs) throw string{ "Can't open file 2" };
	ofs <<'\n' << disemvowels_text;
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
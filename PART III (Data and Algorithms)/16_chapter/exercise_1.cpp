/*
[1]
Write a function, void to_lower(char∗ s), that replaces all uppercase characters in the C-style
string s with their lowercase equivalents. For example, Hello, World! becomes hello, world!.
Do not use any standard-library function. A C-style string is a zero-terminated array of char-
acters, so if you find a char with the value 0 you are at the end.
*/

import PPP;
using namespace std;

void tolower( char* str)
{
	if (!str)return ;
	while (*str)
	{
		if ('A' <= *str && *str <= 'Z')
		{
			*str = *str + 32;
		}
		str++;
	}
}
int main()
try {
	char ch[] = "Hello World!";
	tolower(ch);
	cout << ch << '\n';
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
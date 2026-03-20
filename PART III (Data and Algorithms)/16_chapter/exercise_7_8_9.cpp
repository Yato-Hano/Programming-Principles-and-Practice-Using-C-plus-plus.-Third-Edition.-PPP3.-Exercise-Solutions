/*
[7]
Write a function, string cat_dot(const char∗ s1, const char∗ s2), that concatenates two strings
with a dot in between. For example, cat_dot("Niels", "Bohr") will return a string containing
Niels.Bohr.
[8]
Write a version of cat_dot() that takes const string& arguments.
[9]
Modify cat_dot() from the previous two exercises to take a string to be used as the separator
(rather than dot) as its third argument.
*/

import PPP;
using namespace std;

string cat_dot_s(const string& s1, const string& s2, const string& separator)
{
	return s1 + separator + s2;
}
string convert(const char* s)
{
	string result;
	while (*s)
	{
		result += *s;
		++s;
	}
	return result;
}
string cat_dot(const char* s1, const char* s2, const char* separator)
{
	return convert(s1) + convert(separator) + convert(s2);
}

int main()
try {
	cout << cat_dot("Dan", "com", "@.") << '\n';
	cout << cat_dot_s("Dan_s", "com","@.") << '\n';
	system("pause");
	return 0;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 2;
}
catch (...)
{
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 3;
}
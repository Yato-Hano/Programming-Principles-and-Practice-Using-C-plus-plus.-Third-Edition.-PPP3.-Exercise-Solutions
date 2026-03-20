/*
[4]
Write a function, int str_cmp(const char∗ s1, const char∗ s2), that compares C-style strings.
Let it return a negative number if s1 is lexicographically before s2, zero if s1 equals s2, and a
positive number if s1 is lexicographically after s2. Do not use any standard-library functions.
Do not use subscripting; use the dereference operator ∗ instead.
*/

import PPP;
using namespace std;

int str_cmp(const char* s1, const char* s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	return *s1 - *s2;
}
int main()
try {
	char ch1[] = "123";
	char ch2[] = "124";
	char ch3[] = "12";

	cout << str_cmp(ch1, ch2) << '\n';
	cout << str_cmp(ch1, ch3) << '\n';
	cout << str_cmp(ch1, ch1) << '\n';

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
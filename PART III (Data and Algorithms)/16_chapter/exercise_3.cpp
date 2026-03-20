/*
[3]
Write a function, char∗ find_x(const char∗ s, const char∗ x), that finds the first occurrence of
the C-style string x in s.
*/

import PPP;
using namespace std;

const char* find_x(const char* s, const char* x)
{
	if (!s || !x)return nullptr;

	for (size_t i = 0; s[i]; i++)
	{
		int j = 0;
		while (x[j] && s[i + j] == x[j]) ++j;
		if (x[j] == 0)return &s[i];
	}
	return nullptr;
}
int main()
try {
	char ch1[] = "123456789";
	char ch2[] = "56";
	cout << find_x(ch1, ch2) << '\n';
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
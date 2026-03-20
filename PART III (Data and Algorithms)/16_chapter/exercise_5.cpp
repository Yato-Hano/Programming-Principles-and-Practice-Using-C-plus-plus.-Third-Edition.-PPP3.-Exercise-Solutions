/*
[5]
Consider what happens if you give your str_dup(), find_x(), and str_cmp() a pointer argument
that is not a C-style string. Try it! First figure out how to get a char∗ that doesn’t point to a
zero-terminated array of characters and then use it (never do this in real – non-experimental –
code; it can create havoc). Try it with free-store-allocated and stack-allocated ‘‘fake C-style
strings.’’ If the results still look reasonable, turn off debug mode. Redesign and re-implement
those three functions so that they take another argument giving the maximum number of ele-
ments allowed in argument strings. Then, test that with correct C-style strings and ‘‘bad’’
strings.
*/

import PPP;
using namespace std;

char* str_dup(char* str, int length)
{
	if (!str)return nullptr;
	char* p = new char[length + 1];

	for (size_t i = 0; i < length; i++)
		p[i] = str[i];

	p[length] = 0;

	return p;
}
const char* find_x(const char* s, const char* x, int s_length, int x_length)
{
	if (!s || !x)return nullptr;

	for (int i = 0; i < s_length && s[i]; i++)
	{
		int j = 0;
		while (j < x_length &&
			(i + j) < s_length &&
			x[j] &&
			s[i + j]&&
			s[i + j] == x[j]) 
			++j;

		if (j < x_length && x[j] == 0)return &s[i];
	}
	return nullptr;
}
int str_cmp(const char* s1, const char* s2,int  s1_length)
{
	while (s1_length)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		--s1_length;
	}
	return *s1 - *s2;
}
int main()
try {
	char single_char1 = 'A';
	char single_char2 = 'B';
	char* s_ch1 = &single_char1;
	char* s_ch2 = &single_char2;
	constexpr int max1{ 3 };
	constexpr int max2{ 2 };
	char fa1[] = { 'a','b','c' };
	char fa2[] = { 'b' ,0};
	cout << str_cmp(s_ch1, s_ch1,1) << '\n';
	const char* find_res = find_x(fa1, fa2, max1, max2);
	if (!find_res) cout << "not_found\n";
	cout << find_res << '\n';
	cout << str_dup(s_ch1,1) << '\n';
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
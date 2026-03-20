/*
[10]
Write versions of the cat_dot()s from the previous exercises to take C-style strings as argu-
ments and return a free-store-allocated C-style string as the result. Do not use standard-
library functions or types in the implementation. Test these functions with several strings.
Be sure to free (using delete) all the memory you allocated from free store (using new).
Compare the effort involved in this exercise with the effort involved for exercises 5 and 6.
*/

import PPP;
using namespace std;
int length(const char* s)
{
	int l{ 0 };
	while (s[l])l++;
	return l;
}
char* create_on_free_store(const char* s)
{
	int len{ length(s)};
	
	char* ch_p = new char[len + 1];

	for (size_t i = 0; i < len; i++)
		ch_p[i] = s[i];
	ch_p[len] = 0;
	return ch_p;
}
char* cat_dot(const char* s1, const char* s2, const char* separator)
{
	const int len1{ length(s1) };
	const int len2{ length(s2) };
	const int len3_sep{ length(separator) };
	const int max{ len1 + len2 + len3_sep + 1 };
	char* result = new char[max];

	int index{ 0 };
	for (int i{0}; i < len1; i++,index++)
		result[index] = s1[i];

	for (int i{ 0 }; i < len3_sep; i++, index++)
		result[index] = separator[i];

	for (int i{ 0 }; i < len2; i++, index++)
		result[index] = s2[i];

	result[max-1] =0;
	return result;
}

int main()
try {
	char* res1 = create_on_free_store("12345");
	cout << res1 << '\n';
	delete[]res1;
	char* res2 = cat_dot("Dan", "com", "@.");
	cout << res2 << '\n';
	delete[]res2;
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
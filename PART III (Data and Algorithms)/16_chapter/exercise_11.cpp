/*
[11] 
Rewrite all the functions in §16.5 (palindromes) to use the approach of making a backward
copy of the string and then comparing; for example, take "home", generate "emoh", and com-
pare those two strings to see that they are different, so home isn’t a palindrome.
*/
#include <cstring> 
import PPP;
using namespace std;

bool is_palindrome(const string& s)
{
	string s_rev{ s };
	reverse(s_rev.begin(), s_rev.end());
	return s_rev == s;
}
bool is_palindrome(const char s[],int n)
{
	char* p = new char[n];
	strcpy_s(p,n, s);
	reverse(p, p + n-1);
	bool res = strcmp(p, s);
	delete[]p;
	return !res;
}
bool is_palindrome_sp(span <char >s)
{
	char* p = new char[s.size()];
	strcpy_s(p, s.size(), &s[0]);
	reverse(p, p + s.size() - 1);
	span <char >s2{ p , s.size() };
	bool res = strcmp(p, &s[0]);
	delete[]p;
	return !res;
}
bool is_palindrome(const char* first, const char* last)
{
	int len{ 1 };
	for (const char* i = first; i < last; i++, len++);
	char* p = new char[len];
	strcpy_s(p, len, first);
	reverse(p, p + len - 1);
	bool res = strcmp(p, first);
	delete[]p;
	return !res;
}
int main()
try {
	cout << is_palindrome("121") << '\n';
	cout << is_palindrome("home") << '\n';
	char ch1[] = "121";
	char ch2[] = "home";
	cout << is_palindrome(ch1, sizeof(ch1)) << '\n';
	cout << is_palindrome(ch2, sizeof(ch2)) << '\n';
	cout << is_palindrome_sp(ch1) << '\n';
	cout << is_palindrome_sp(ch2) << '\n';
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
/*
[2]
Write a function, char∗ str_dup(const char∗), that copies a C-style string into memory it allo-
cates on the free store. Do not use any standard-library function.
*/

import PPP;
using namespace std;

char* str_dup(char* str)
{
	if (!str)return nullptr;
	int length{};
	while (str[length])
		++length;
	char* p = new char[length + 1];
	for (size_t i = 0; i < length; i++)
		p[i] = str[i];
	p[length] = 0;

	return p;
}
int main()
try {
	char ch[] = "Hello World!";
	cout << str_dup(ch) << '\n';
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
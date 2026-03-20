/*

*/

import PPP;
using namespace std;

void copy_(int* f1, int* e1, int* f2)
{
	while (f1 < e1)
	{
		*f2 = *f1;
		f1++;
		f2++;
	}
}

template<typename Iter>
	requires bidirectional_iterator<Iter>
void advance(Iter& p, int n)
{
	while (0 < n)
	{
		++p;
		--n;
	}
	while (n <0 )
	{
		--p;
		++n;
	}
}
template<typename Iter>
	requires forward_iterator<Iter>
bool match(Iter f, Iter l, const string s)
{
	auto s_it = s.begin();
	while( s_it != s.end() && f != l)
	{
		if (*s_it != *f) return false;
		++f;
		++s_it;
	}
	return s_it == s.end() && f == l;
}

template<typename T>
size_t number_of_elements(const list<T>& s)
{
	return s.size();
}
size_t number_of_elements(span<const char> s)
{
	return s.size();
}
size_t number_of_elements(span<const int> s)
{
	return s.size();
}
template<typename T>
void tetst_alg(const T& container)
{
	cout << "number_of_elements "<< container.size() << '\n';
	cout << "match "<< match(container.begin(), container.end(), "Hello") << '\n';
	string str_hwd = "Howdy";
	auto result = lexicographical_compare_three_way(container.begin(), container.end(), str_hwd.begin(), str_hwd.end());
	if (result < 0) {
		std::cout << "a is less than b" << std::endl;
	}
	else if (result > 0) {
		std::cout << "a is greater than b" << std::endl;
	}
	else { // result == 0
		std::cout << "a is equal to b" << std::endl;
	}
}
int main()
try {
	vector<char>v_hl{ 'H','e','l','l','o' };
	list<char>l_hl{ 'H','e','l','l','o' };
	char ar_hl[]{ 'H','e','l','l','o' };
	string str_hl = "Hello";
	tetst_alg(v_hl);
	tetst_alg(l_hl);
	tetst_alg(str_hl);
	cout << number_of_elements(ar_hl) << '\n';
	cout << '\n';
	span<char> ar_hlsp{ ar_hl };
	cout << match(ar_hlsp.begin(), ar_hlsp.end(), "Hello") << '\n';
	cout << '\n';

	system("pause");

	vector<int>v_hln{ 1,2,3,4,5 };
	list<int>l_hln{ 1,2,3,4,5 };
	int ar_hln[]{ 1,2,3,4,5 };
	tetst_alg(v_hln);
	tetst_alg(l_hln);
	cout << number_of_elements(ar_hln) << '\n';
	cout << '\n';
	span<int> ar_hlspn{ ar_hln };
	cout << match(ar_hlspn.begin(), ar_hlspn.end(), { 1,2,3,4,5 }) << '\n';
	cout << '\n';
	system("pause");
	vector<int>v1{ 1,2,3,4,5 };
	vector<int>v2(10);
	cout << "copy_()\n";
	copy_(&v1[0], &v1[v1.size()-1]+1, &v2[0]);
	for (int n : v2)cout << n << ' ';
	cout << '\n';

	cout << "advance()\n";
	auto it = v1.begin();
	advance(it, 2);
	cout << *it << '\n';

	auto it2 = v1.end();
	advance(it2, -2);
	cout << *it2 << '\n';

	string s{ "fsajkl" };
	string s2{ "fsajkl2" };
	cout << "match()\n";
	cout << match(s.begin(), s.end(), s) << '\n';
	cout << match(s.begin(), s.end(), s2) << '\n';
	cout << match(s2.begin(), s2.end(), s) << '\n';
	cout << match(s2.begin(), s2.end(), "") << '\n';

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
/*
[3]
Implement count() yourself. Test it.
[4]
Implement count_if() yourself. Test it.
*/

import PPP;
using namespace std;

template<ranges::input_range R,class T>
[[nodiscard]]
size_t count_(const R& r,const T&v)
{
	auto first = ranges::begin(r);
	auto last = ranges::end(r);
	size_t number{ 0 };
	while (first != last)
	{
		if (*first == v)++number;
		++first;
	}
	return number;
}
template<ranges::input_range R, invocable<ranges::range_reference_t<R>> Op>
[[nodiscard]]
size_t count_if_(const R& r, Op o)
{
	auto first = ranges::begin(r);
	auto last = ranges::end(r);
	size_t number{ 0 };
	while (first != last)
	{
		if (o(*first))++number;
		++first;
	}
	return number;
}

int main()
try {
	int n[5]{1,2,5,3,5};
	cout << count_(n,5)<< '\n';
	cout << count_if_(n, [](int x) {return x < 5; }) <<'\n';
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
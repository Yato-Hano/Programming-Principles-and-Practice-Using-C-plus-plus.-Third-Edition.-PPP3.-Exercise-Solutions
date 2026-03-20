/*

*/

import PPP;
using namespace std;

template<input_iterator In, class T>
[[nodiscard]]
pair<In,bool> find_(In first, In last, const T& v)
{
	while (first != last)
	{
		if (*first == v)return { first ,true };
		++first;
	}
	if (*first == v)return { first ,true };
	return { first ,false};
}

template<input_iterator In, class T>
[[nodiscard]]
size_t count_(In first, In last, const T& v)
{
	size_t number{ 0 };
	while (first != last)
	{
		if (*first == v)++number;
		++first;
	}
	if (*first == v)++number;
	return number;
}
int main()
try {
	vector<int> v{5, 1,2,5,3,5 };

	cout << count_(v.begin(),--v.end(), 5) << '\n';

	vector<int> v2{ 5, 1,2,3,7};

	if (auto found = find_(v2.begin(), --v2.end(), 5); found.second)
		cout << "Found " << *found.first << '\n';

	if (auto found = find_(v2.begin(), --v2.end(), 7); found.second)
		cout << "Found " << *found.first << '\n';

	if (auto found = find_(v2.begin(), --v2.end(), 11); found.second)
		cout << "Found " << *found.first << '\n';
	else 
		cout << "Not found 11.\n";

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
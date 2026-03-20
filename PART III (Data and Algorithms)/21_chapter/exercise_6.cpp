/*

*/

import PPP;
using namespace std;

template<ranges::random_access_range Ran, equality_comparable T>
[[nodiscard]]
bool binary_search_(const Ran& r, const T& val)
{
	if (r.empty())return false;
	if (!is_sorted(r.begin(),r.end()))throw exception{ "random_access_range Ran is not sorted" };

	double index( (r.size()-1)/2.0 ); // middle index
	double shift{ index /2 };
	while ( 0.1<shift && r[round(index)] != val)
	{
		if (val< r[round(index)] )
			index -= shift;
		else
			index += shift;

		shift /= 2.0;
	}
	if (r[round(index)] == val) return true;
	return false;
}
int main()
try {
	vector<int> v{ 1,2,3,4,5
	//,6
	};

	cout << "0 found: " << binary_search_(v, 0) << '\n';
	cout << "1 found: " << binary_search_(v, 1) << '\n';
	cout << "2 found: " << binary_search_(v, 2) << '\n';
	cout << "3 found: " << binary_search_(v, 3) << '\n';
	cout << "4 found: " << binary_search_(v, 4) << '\n';
	cout << "5 found: " << binary_search_(v, 5) << '\n';
	cout << "6 found: " << binary_search_(v, 6) << '\n';
	cout << "7 found: " << binary_search_(v, 7) << '\n';


	vector<string> vs{ "1","2","3","4","5","6"};

	cout << "\n\n0 found: " << binary_search_(vs, "0") << '\n';
	cout << "1 found: " << binary_search_(vs, "1") << '\n';
	cout << "2 found: " << binary_search_(vs, "2") << '\n';
	cout << "3 found: " << binary_search_(vs, "3") << '\n';
	cout << "4 found: " << binary_search_(vs, "4") << '\n';
	cout << "5 found: " << binary_search_(vs, "5") << '\n';
	cout << "6 found: " << binary_search_(vs, "6") << '\n';
	cout << "7 found: " << binary_search_(vs, "7") << '\n';
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
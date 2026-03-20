/*

*/

import PPP;
using namespace std;
template<typename iter>
void initialize_with_increaesed(iter first, iter last)
{
	int number{ 0 };
	while (first != last)
	{
		*first = number;
		++number;
		++first;
	}
}
template<typename iter>
void print_arr(iter first, iter last)
{
	while (first != last)
	{
		cout<< *first <<' ';
		++first;
	}
	cout << '\n';
}
template<typename iter, typename val>
void increaese_by(iter first, iter last,const val& v)
{
	while (first != last)
	{
		*first += v;
		++first;
	}
}

template<input_iterator Iter1, output_iterator<iter_value_t<Iter1>> Iter2>
Iter2 copy_(Iter1 f1, Iter1 e1, Iter2 f2)
{
	while (f1 != e1)
	{
		*f2 = *f1;
		f1++;
		f2++;
	}
	return f2;
}
template<typename iter, typename val>
int find_index(iter f, iter l, val v)
{
	iter ff = std::find(f, l, v);
	if (ff == l)return -1;
	return std::distance(f, ff);
}
int main()
try {
	constexpr int max{ 10 };
	int arr[max]{};
	initialize_with_increaesed(arr, arr + max);
	print_arr(arr, arr + max);
	vector<int> vn(max);
	initialize_with_increaesed(vn.begin(), vn.end());
	print_arr(vn.begin(), vn.end());
	list<int> ln(max);
	initialize_with_increaesed(ln.begin(), ln.end());
	print_arr(ln.begin(), ln.end());


	cout << "2:\n";
	int arr2[max];
	copy_(arr, arr + max, arr2);
	vector<int> vn2(vn);
	list<int> ln2(ln);
	print_arr(arr2, arr2 + max);
	print_arr(vn2.begin(), vn2.end());
	print_arr(ln2.begin(), ln2.end());

	cout << "increaese_by():\n";
	increaese_by(arr2, arr2 + max, 2);
	increaese_by(vn2.begin(), vn2.end(), 3);
	increaese_by(ln2.begin(), ln2.end(),5);

	cout << "arr2: ";
	print_arr(arr2, arr2 + max);
	cout << "vn2: ";
	print_arr(vn2.begin(), vn2.end());
	cout << "ln2: ";
	print_arr(ln2.begin(), ln2.end());

	cout << "copy_()\n";
	copy_(arr2, arr2 + max, vn2.begin());
	copy_(ln2.begin(), ln2.end(), arr2);
	cout << "vn2: ";
	print_arr(vn2.begin(), vn2.end());
	cout << "arr2: ";
	print_arr(arr2, arr2 + max);

	cout << "find()\n";
	cout <<"vector index for 3: " << find_index(vn2.begin(), vn2.end(), 3) << '\n';
	cout << "list index for 27: " << find_index(ln2.begin(), ln2.end(), 27) << '\n';


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
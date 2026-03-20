/*
[21] 
Define and test a Checked_iterator; that is, an iterator that ‘‘knows’’ the size of its range and
throws an exception if we try to access outside that. Hint: §20.7.2.
*/

import PPP;
using namespace std;

template<typename T>
class Checked_iterator {
	using iter = T::iterator;
	iter it;
	const iter first;
	const iter last;
public:
	Checked_iterator(iter i, iter f, iter l)
		:it{ i }, first{ f }, last{ l }
	{
	}
	T::value_type& operator*() { 
		if (it == last) throw out_of_range{ "dereferencing end iterator" };
		return *it; }
	Checked_iterator& operator++() {
		if (it == last) throw out_of_range{ "incrementing end iterator" };
		++it;
		return *this;
	}
	Checked_iterator& operator--() {
		if (it == first) throw out_of_range{ "decreasing begin iterator" };
		--it;
		return *this;
	}
	bool operator==(const Checked_iterator& other)const { return it == other.it; }
	bool operator!=(const Checked_iterator& other)const { return it != other.it; }
};

int main()
try {
	vector<int> v{ 1,2,3 };
	
	for (Checked_iterator<vector<int>> civ{ v.begin(),v.begin(),v.end() }; true; ++civ)
		//cout << *civ << '\n'
		;
	cout << '\n';
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
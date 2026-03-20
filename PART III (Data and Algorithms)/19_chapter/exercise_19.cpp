/*
[19] 
Define a range-checked iterator for list (a bidirectional iterator).
*/

import PPP;
using namespace std;

template<typename T>
class My_List {
	list<T>l;
public:
	void push_back(const T& t) { l.push_back(t); }
	class iterator;

	iterator begin() { return iterator{ l.begin(),l.begin(),l.end() }; }
	iterator end() { return iterator{ l.end(),l.begin(),l.end() }; }
};
template<typename T>
class My_List<T>::iterator {
	list<T>::iterator it;
	const list<T>::iterator first;
	const list<T>::iterator last;
public:
	iterator(list<T>::iterator i, list<T>::iterator f, list<T>::iterator l)
		:it{ i }, first{ f }, last{ l }
	{
	}
	T& operator*() { return *it; }
	iterator& operator++() {
		if (it == last) throw out_of_range{ "incrementing end iterator" };
		++it;
		return *this;
	}
	iterator& operator--() {
		if (it == first) throw out_of_range{ "decreasing begin iterator" };
		--it;
		return *this;
	}
	bool operator==(const iterator& other)const { return it == other.it; }
	bool operator!=(const iterator& other)const { return it != other.it; }
};

int main()
try {
	My_List<int>n;
	n.push_back(5);

	for (int nn : n)cout << nn << '|';
	cout << '\n';
	//--n.begin();
	//++++n.end();
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
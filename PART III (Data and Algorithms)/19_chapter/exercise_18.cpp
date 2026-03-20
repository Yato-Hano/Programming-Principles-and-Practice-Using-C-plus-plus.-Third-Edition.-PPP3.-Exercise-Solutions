/*
[18] 
Define a range-checked iterator for vector (a random-access iterator).
*/

import PPP;
using namespace std;

template<typename T>
class My_Vector {
	vector<T>v;
public:
	void push_back(const T& t) { v.push_back(t); }
	class iterator;

	iterator begin() { return iterator{ v.begin(),v.begin(),v.end() }; }
	iterator end() { return iterator{v.end(),v.begin(),v.end()}; }
};
template<typename T>
class My_Vector<T>::iterator {
	vector<T>::iterator it;
	const vector<T>::iterator first;
	const vector<T>::iterator last;
public:
	iterator(vector<T>::iterator i, vector<T>::iterator f, vector<T>::iterator l)
		:it{i}, first{ f}, last{ l}
	{ 
	}
	T& operator*() { return *it; }
	T& operator[](int n) {
		if (0 < n && last-it<=n) throw out_of_range{ "subscripting+: out of range iterator" };
		else
			if (n < 0 &&  it-first < abs(n) ) throw out_of_range{ "subscripting-: out of range iterator" };
		return *iterator{ it + n,first,last};
	}
	iterator& operator++() {
		if(it==last) throw out_of_range{ "incrementing end iterator" };
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
	My_Vector<int>n;
	n.push_back(5);
	cout << n.begin()[-1]<< '\n';

	for (int nn : n)cout << nn <<'|';
	cout<<'\n';
	//--n.begin();
	//++n.end();
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
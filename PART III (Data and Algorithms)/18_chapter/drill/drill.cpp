/*

*/

import PPP;
using namespace std;
template<typename T>
struct S {
	S(T v);
	S(const S<T>& v);
	S& operator=(const S<T>& );
	T& access();
	const T& access() const;
private:
	T val;
};

template<typename T>
 T& S< T>::access()
{
	return val;
}
 template<typename T>
 const T& S< T>::access()const
 {
	 return val;
 }
template<typename T>
S< T>::S(const S<T>& v)
	:val{ v.val }
{	}
template<typename T>
S<T>& S< T>::operator=(const S<T>& v)
{
	cout << "assign\n";
	//swap(*this, v);
	val = v.val;
	return *this;
}

template<typename T>
S< T>::S( T v)
	:val{v}
{}

template<typename T>
void read_val(T& v)
{
	cin >> v;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& v)
{
	char ch{};
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	v.clear();
	for (T val{}; is>>val; )
	{
		v.push_back(val);
		is >> ch;
		if (ch != ',')break;
	}
	if (ch == '}')
		return is;
	else throw exception{ "Bad reading" };
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << "{ ";
	for (size_t i = 0; i < v.size(); i++)
	{
		os << v[i]; 
		if ((1 + i) < v.size())	os << ',';
		os << ' ';
	}
	os << '}';
	return os;
}

int main()
try {
	vector<int> vc{ 1,3,4,2 };
	cout << vc <<'\n';

	S<int> n{ 2 };
	S<vector<int>> v{ vector<int> ()};
	cout << "v: ";
	read_val(v.access());
	cout << "v: " << v.access() << '\n';

	cout << "n: ";
	read_val(n.access());
	cout << "n: "<<n.access()<<'\n';
	/*
	int a{ 1 };
	int b{ 2 };
	const int* pa = &a;
	const int* pb = &b;
	cout << pa <<' '<<*pa<<'\n';
	cout << pb << ' ' << *pb << '\n';
	cout << '\n';
	swap(pa, pb);
	cout << pa << ' ' << *pa << '\n';
	cout << pb << ' ' << *pb << '\n';
	*/
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
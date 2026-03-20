/*
[6]
Repeat the previous exercise, but with a class Number<T> where T can be any numeric
type. Try adding % to Number and see what happens when you try to use % for Num-
ber<double> and Number<int>.
*/

import PPP;
using namespace std;

template<typename T>
class Number
{
public:
	Number() :value{ } {}
	Number(T n) :value{ n } {}
	T value;
	auto operator<=>(const Number&)const = default;
};
template<typename T>
Number<T> operator+(const Number<T>& n1, const Number<T>& n2)
{
	return n1.value + n2.value;
}
template<typename T>
Number<T> operator-(const Number<T>& n1, const Number<T>& n2)
{
	return n1.value - n2.value;
}
template<typename T>
Number<T> operator*(const Number<T>& n1, const Number<T>& n2)
{
	return n1.value * n2.value;
}
template<typename T>
Number<T> operator/(const Number<T>& n1, const Number<T>& n2)
{
	return n1.value / n2.value;
}
template<typename T>
Number<T> operator%(const Number<T>& n1, const Number<T>& n2)
{
	return n1.value % n2.value;
}
template<typename T>
ostream& operator<<(ostream& os, const Number<T>& n)
{
	return os << n.value;
}
template<typename T>
istream& operator>>(istream& is, Number<T>& n)
{
	return is >> n.value;
}
int main()
try {
	Number<int> n = 5;
	Number<int> v = 5.2;
	n = v;
	cout << v % n << '\n';
	cout << (n == v) << '\n';
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
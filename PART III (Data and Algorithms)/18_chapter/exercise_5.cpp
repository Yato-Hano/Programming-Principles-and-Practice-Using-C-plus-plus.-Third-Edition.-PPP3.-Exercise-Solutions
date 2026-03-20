/*
[5]
Define a class Int having a single member of class int. Define constructors, assignment,
and operators +, −, ∗, / for it. Test it, and improve its design as needed (e.g., define opera-
tors << and >> for convenient I/O).
*/

import PPP;
using namespace std;

class Int
{
public:
	Int(int n) :value{ n } {}
	int value{ 0 };
	auto operator<=>(const Int&)const = default;
};
Int operator+(const Int& n1, const Int& n2)
{
	return n1.value + n2.value;
}
Int operator-(const Int& n1, const Int& n2)
{
	return n1.value - n2.value;
}
Int operator*(const Int& n1, const Int& n2)
{
	return n1.value * n2.value;
}
Int operator/(const Int& n1, const Int& n2)
{
	return n1.value / n2.value;
}
ostream& operator<<(ostream& os, const Int& n)
{
	return os << n.value;
}
istream& operator>>(istream& is, Int& n)
{
	return is>> n.value;
}
int main()
try {
	Int n = 5;
	Int v=5.2;


	n=v;
	cout << v+n << '\n';
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
/*
[2]
Write a template function that takes a vector<T> vt and a vector<U> vu as arguments and
returns the sum of all vt[i]∗vu[i]s.
[7]
Try your solution to exercise 2 with some Numbers.
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
Number<T> operator*(const Number<T>& n1, const Number<T>& n2)
{
	return n1.value * n2.value;
}
template<typename T>
Number<T> operator+=( Number<T>& n1, const Number<T>& n2)
{
	return n1.value += n2.value;
}
template<typename T, typename U  >
T mult_sum(const vector<T>& vt, const vector<U>& vu)
{
	if (vt.size() != vu.size())throw out_of_range{"mult_sum: different sizes"};
	T sum{ 0 };
	for (size_t i = 0; i < vt.size(); i++)
		sum+= vt[i] * vu[i];
	return sum;
}

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& n)
{
	return os << n.value;
}
int main()
try {
	vector<Number<int>>v1{ 0,1,2,3,5 };
	vector<Number<int>>v2{ 0,1,2,3,5 };

	cout << mult_sum(v1, v2) << '\n';

	v1.push_back(5);
	mult_sum(v1, v2);

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
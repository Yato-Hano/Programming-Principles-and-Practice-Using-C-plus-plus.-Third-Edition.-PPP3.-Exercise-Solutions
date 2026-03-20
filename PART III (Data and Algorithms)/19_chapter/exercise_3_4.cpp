/*
[3]
Look at the palindrome examples (§16.5); redo the Jack-and-Jill example from §19.2.1 using
that variety of techniques.
[4]
Find and fix the errors in the Jack-and-Jill example from §19.2.1 by using STL techniques
throughout.
*/

import PPP;
using namespace std;

template<forward_iterator Iter>
Iter high(Iter first, Iter last)
{
	Iter high = first;
	for (Iter p = first; p != last; ++p)
		if (*high < *p)
			high = p;
	return high;
}
double* get_from_jack(int* count)
{
constexpr	int max{ 30 };
	double* data = new double[max];
	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "no file" };
	for (int i = 0; i < max && ifs >> data[i]; i++, (*count)++)
	{
	}

	return data;
}
vector<double> get_from_jill()
{
	vector<double> v;
	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "no file" };
	for (double d{}; ifs >> d;)
		v.push_back(d);
	return v;
}

void fct_count()
{
	int jack_count = 0;
	double* jack_data_raw = get_from_jack(&jack_count);
	vector<double> jack_data(jack_data_raw, jack_data_raw + jack_count);
	delete[] jack_data_raw;
	vector<double> jill_data = get_from_jill();

	vector<double>::iterator jack_high = high(jack_data.begin(), jack_data.end());
	vector<double>::iterator jill_high = high(jill_data.begin(), jill_data.end());

	if (jill_high != jill_data.end())
		cout << "Jill's high " << *jill_high << '\n';
	if (jack_high != jack_data.end())
		cout << "; Jack's high " << *jack_high << '\n';

}


double* get_from_jack2(double*& last)
{
	constexpr	int max{ 30 };
	double* data = new double[max];
	last = data;
	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "no file" };
	for (int i = 0; i < max && ifs >> data[i]; i++, last++)
	{
	}

	return data;
}
void fct_pointers()
{
	double* jack_data_raw_l{nullptr};
	double* jack_data_raw_f = get_from_jack2(jack_data_raw_l);
	vector<double> jack_data(jack_data_raw_f, jack_data_raw_l);
	delete[] jack_data_raw_f;

	vector<double>::iterator jack_high = high(jack_data.begin(), jack_data.end());
	if (jack_high != jack_data.end())
		cout << "; Jack's high " << *jack_high << '\n';
}
int main()
try {
	fct_count();
	fct_pointers();
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
/*
[2]
Get the Jack-and-Jill example from §19.2.1 to work. Use input from a couple of small files
to test it.
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
	int max{ 10 };
	double*  data = new double[max];
	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "no file" };
	for (int i = 0; i < 10&& ifs>> data[i]; i++,*count++)
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

void fct()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double> jill_data = get_from_jill();

	double* jack_high = high(jack_data, jack_data + jack_count);
	vector<double>::iterator jill_high = high(jill_data.begin(), jill_data.end());

	cout << "Jill's high " << *jill_high 
		<< "; Jack's high " << *jack_high<<'\n';

	delete[] jack_data;
}
int main()
try {
	fct();
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
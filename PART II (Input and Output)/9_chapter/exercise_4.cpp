/*
[4]
Write a program called multi_input.cpp that prompts the user to enter several integers in any
combination of octal, decimal, or hexadecimal, using the 0 and 0x base prefixes; interprets the
numbers correctly; and converts them to decimal form. Then your program should output the
values in properly spaced columns like this:
0x43 hexadecimal converts to 67 decimal
0123 octal		 converts to 83 decimal
 65	 decimal	 converts to 65 decimal
*/

import PPP;
using namespace std;

enum class Base {
	oct,hex,dec,No_base
};

vector<string> literals_table{ "octal","hexadecimal","decimal" };

Base get_base(istream&is)
{
	char ch{' '};
	if (!(is >> ch) || !iswdigit(ch))
		return Base::No_base; //give up;
	
	switch (ch)
	{
	case '0':
		if (is.get(ch)&&ch == 'x')
			return Base::hex;
		else
			if (iswdigit(ch)) { 
				is.putback(ch);
				return Base::oct; 
			}
		break; //give up;
	default:
		is.putback(ch);
		return  Base::dec;
	}
	return Base::No_base;
}
//pair of the base of original input and the decimal value
pair<Base,int> get_decimal_value(const string& s)
{
	istringstream is{ s };
	Base original_base{ get_base(is) };
	int dec_value{ 0 };
	switch (original_base)
	{
	case Base::dec:
		is >> dec >> dec_value;
		break;
	case Base::hex:
		is >> hex >> dec_value;
		break;
	case Base::oct:
		is >> oct >> dec_value;
		break;
	default:
		throw exception{ "Bad input: not hexadecimal, octal or decimal" };
	}
	is >> dec; // reset
	return { original_base ,dec_value };
}
int main()
try {
	string value;
	while (cin>> value)
	{
		pair<Base, int> bi = get_decimal_value(value);
		cout << left <<setw(7) << value<<setw(15)<< literals_table[int(bi.first)] << "\tconverts to\t" << bi.second << "\tdecimal\n";
	}
	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
	return 1;
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
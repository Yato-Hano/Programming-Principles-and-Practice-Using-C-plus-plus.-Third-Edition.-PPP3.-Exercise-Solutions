/*
[21] 
Define a Roman_int class for holding Roman numerals (as ints) with a << and >>. Provide
Roman_int with an as_int() member that returns the int value, so that if r is a Roman_int, we
can write cout << "Roman" << r << " equals " << r.as_int() << ’\n’;.
*/

import PPP;
using namespace std;

inline bool is_there(char ch, const string& w)
{
    for (char c : w)if (ch == c)return true;
    return false;
}

bool is_valid(const string& s)
{
    for (char ch : s)if (!is_there(ch,"IVXLCDM"))return false;
    return true;
}

unsigned int roman_to_int(const string& s)
{
    map<char, int> roman;
    roman['I'] = 1;
    roman['V'] = 5;
    roman['X'] = 10;
    roman['L'] = 50;
    roman['C'] = 100;
    roman['D'] = 500;
    roman['M'] = 1000;

    unsigned int total = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i < s.size() - 1 && roman[s[i]] < roman[s[i + 1]]) {
            total -= roman[s[i]];
        }
        else {
            total += roman[s[i]];
        }
    }
    return total;
}

string int_to_roman(unsigned int n) 
{
    vector<int> values  { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    vector<string> symbols  { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

    string result = "";

    for (int i = 0; i < symbols.size(); ++i)
    {
        while (n >= values[i])
        {
            result += symbols[i];
            n -= values[i];
        }
    }
    return result;
}

class Roman_int {
public:
    Roman_int(string val);
    Roman_int(unsigned int val);
    const unsigned int& as_int() const { return value; }
    const string& as_roman() const { return roman_number; }
private:
    string roman_number;
    unsigned int value{ 0 };
};
Roman_int::Roman_int(string val) 
    :value{ roman_to_int (val)}, roman_number{val}
{
    if (!is_valid(val)) throw exception{ "Roman_int: bad literal" };
}
Roman_int::Roman_int(unsigned int val)
    :value{ val },roman_number{ int_to_roman (val)}
{}
ostream& operator<<(ostream& os, const Roman_int& r)
{
    return os << r.as_roman();
}
istream& operator>>(istream& is, Roman_int& r)
{
    string s;
    is >>s;
    r = Roman_int{ s };
    return is;
}

int main()
try {
    string sv;
    unsigned int vi{};
    while (cin)
    {
        cout << "> ";
        Roman_int r1{""};
        cin >> r1 >> vi;
        Roman_int r2{ vi };
        cout << "Roman r1 " << r1 << " equals " << r1.as_int() << '\n';
        cout << "Roman r2 " << r2.as_roman() << " equals " << r2.as_int() << '\n';
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
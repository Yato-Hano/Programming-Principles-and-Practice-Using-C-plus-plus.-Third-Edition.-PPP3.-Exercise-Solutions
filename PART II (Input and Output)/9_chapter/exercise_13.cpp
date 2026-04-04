/*
[13] 
Write a program that reads a text file and writes out how many characters of each character
classification (§9.10.3) are in the file.
*/

import PPP;
using namespace std;

struct Classification
{
	Classification(){}
	Classification(char);
	char simbol{};
	unsigned int space{ 0 };
	unsigned int alpha{ 0 };
	unsigned int digit{ 0 };
	unsigned int upper{ 0 };
	unsigned int lower{ 0 };
	unsigned int alnum{ 0 };
	unsigned int cntrl{ 0 };
	unsigned int punct{ 0 };
	unsigned int print{ 0 };
	unsigned int graph{ 0 };
};
Classification::Classification(char c)
	:simbol(c), space{ bool(isspace(c)) }, alpha{ bool(iswalpha(c)) }
	, digit{ bool(isdigit(c)) }, upper{ bool(isupper(c)) }, lower{ bool(iswlower(c)) }
	, alnum{ bool(iswalnum(c)) }, cntrl{ bool(iswcntrl(c)) }, punct{ bool(iswpunct(c)) }
	, print{ bool(isprint(c)) }, graph{ bool(isgraph(c)) }
{
}
void operator+=(Classification& c1, const Classification& c2)
{
	c1.space += c2.space;
	c1.alpha += c2.alpha;
	c1.digit += c2.digit;
	c1.upper += c2.upper;
	c1.lower += c2.lower;
	c1.alnum += c2.alnum;
	c1.cntrl += c2.cntrl;
	c1.punct += c2.punct;
	c1.print += c2.print;
	c1.graph += c2.graph;
}

ostream& operator<<(ostream& os, const Classification& c)
{
	return	os<<c.space << " isspace\n"
	<< c.alpha  << " isalpha\n"
	<< c.digit  << " isdigit\n"
	 << c.upper  << " isupper\n"
	 << c.lower  << " islower\n"
	 << c.alnum  << " isalnum\n"
	 << c.cntrl  << " iscntrl\n"
	 << c.punct  << " ispunct\n"
	 << c.print  << " isprint\n"
	 << c.graph  << " isgraph\n";
}

int main()
try {
	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "No file" };
	Classification summ;
	for (char i = 0; ifs>>i;)
	{
		summ += Classification{ i };
	}
	cout << summ<<'\n';
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
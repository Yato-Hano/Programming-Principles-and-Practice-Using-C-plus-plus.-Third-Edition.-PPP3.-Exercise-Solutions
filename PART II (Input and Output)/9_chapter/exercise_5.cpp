/*
[5]
Write a program that reads strings and for each string outputs the character classification of
each character, as defined by the character classification functions presented in §9.10.3. Note
that a character can have sev eral classifications (e.g., x is both a letter and an alphanumeric).
*/

import PPP;
using namespace std;
struct Classification
{
	Classification(char c);
	char simbol;
	bool space;
	bool alpha;
	bool digit;
	bool upper;
	bool lower;
	bool alnum;
	bool cntrl;
	bool punct;
	bool print;
	bool graph;

};
Classification::Classification(char c)
	:simbol(c),space{bool(isspace(c))},alpha{ bool(iswalpha(c))}
	,digit{ bool(isdigit(c))},upper{ bool(isupper(c))},lower{ bool(iswlower(c))}
	,alnum{ bool(iswalnum(c))},cntrl{ bool(iswcntrl(c))},punct{ bool(iswpunct(c))}
	,print{ bool(isprint(c))},graph{ bool(isgraph(c))}
{}

ostream& operator<<(ostream& os, const Classification& c)
{
	os << c.simbol << ' ';
	if (c.space) os << " isspace,";
	if (c.alpha) os << " isalpha,";
	if (c.digit) os << " isdigit,";
	if (c.upper) os << " isupper,";
	if (c.lower) os << " islower,";
	if (c.alnum) os << " isalnum,";
	if (c.cntrl) os << " iscntrl,";
	if (c.punct) os << " ispunct,";
	if (c.print) os << " isprint,";
	if (c.graph) os << " isgraph,";
	return os;
}

void classify(const string& word)
{
	for (char c : word) cout << Classification{ c } << '\n';
}
int main()
try {
	for (string word; cin;)
	{
		cout << "> ";
		cin >> word;
		classify(word);
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
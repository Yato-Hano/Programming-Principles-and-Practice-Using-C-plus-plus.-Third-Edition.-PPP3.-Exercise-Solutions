/*
[9]
Write a function vector<string> split(const string& s) that returns a vector of whitespace-sepa-
rated substrings from the argument s.
[10] 
Write a function vector<string> split(const string& s, const string& w) that returns a vector of
whitespace-separated substrings from the argument s, where whitespace is defined as ‘‘ordi-
nary whitespace’’ plus the characters in w.
*/

import PPP;
using namespace std;

bool is_there(char ch, const string& w)
{
	for (char c : w)if (ch == c)return true;
	return false;
}
bool is_space(char ch, const string& w)
{
	return iswspace(ch) || is_there(ch, w);
}


string skip_get_word(istream& is,const string& w)
{
	char ch{};
	while (is.get(ch) && is_space(ch,w)); //skip

	is.putback(ch);

	string word;
	while (is.get(ch) && !is_space(ch,w))word += ch;
	is.putback(ch);

	return word;
}
vector<string> split(const string&ss, const string& w)
{
	istringstream is(ss);
	vector<string> vs;
	string word;
	for (char ch{}; is.get(ch);)
	{
		vs.push_back(skip_get_word(is,w));
	}
	return vs;
}

vector<string> split(const string& ss)
{
	istringstream is(ss);
	vector<string> vs;
	string s;
	while (is >> s)
		vs.push_back(s);
	return vs;
}

int main()
try {
	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "Noo file" };

	string text{
		istreambuf_iterator<char>(ifs),
		istreambuf_iterator<char>()
	};
	vector<string> list{ split (text,"?^")};

	for (string word : list)
		cout << word << '\n';
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
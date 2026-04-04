/*
[7]
Modify the program from the previous exercise so that it replaces don’t with do not, can’t
with cannot, etc.; leaves hyphens within words intact (so that we get ‘‘ do not use the as−if
rule ’’); and converts all characters to lowercase.
[8]
Use the program from the previous exercise to make a sorted list of words. Run the result on
a multi-page text file, look at the result, and see if you can improve the program to make a
better list.
*/

import PPP;
using namespace std;


string get_lowered_word(istream& is)
{
	char ch{};
	string word;
	while (is.get(ch) && (iswalpha(ch)||ch=='-'||ch=='\''))word += tolower(ch);
	is.putback(ch);
	return word;
}
string replace_word(string word)
{
	static vector<pair<string, string>> equivalence_table{ {"don't","do not"},
															{"can't","cannot"} };
	for (pair<string, string> p : equivalence_table) if (p.first == word) return p.second;
	return word;
}

string normalize(istream& is)
{
	string new_text;
	for (char ch{}; is.get(ch) ;)
	{
		if(!iswalpha(ch))
			new_text += ch;
		else {
			is.putback(ch);
			new_text += replace_word(get_lowered_word(is));
		}
	}
	return new_text;
}


vector<string> make_list(const string& text)
{
	vector<string> list;
	istringstream is{ text };
	
	for (char ch{}; is.get(ch);)
	{
		if (iswalpha(ch))
		{
			is.putback(ch);
			list.push_back( get_lowered_word(is));
		}
	}

	sort(list.begin(), list.end());
	return list;
}

vector<string> make_unique_list(const vector<string>& l)
{
	vector<string> list;
	string prev;
	for (string word : l) {
		if(prev!=word)
			list.push_back(word);
		prev = word;
	}
	return list;
}
int main()
try {
	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "Noo file" };
	vector<string> list = make_unique_list(make_list(normalize(ifs)));
	
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
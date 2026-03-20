/*
[1]
Rewrite the word-counting program from §20.2 to not distinguish between uppercase and
lowercase letters and to treat punctuation characters as whitespace.
[3]
Take the word-frequency example from §20.2 and modify it to output its lines in order of fre-
quency (rather than in lexicographical order). An example line would be 3: C++ rather than
C++: 3.
*/

import PPP;
using namespace std;

void skip_until_letter(istream& is)
{
	char ch{};
	while (is.get(ch) && (iswspace(ch)|| iswpunct(ch)));
	is.putback(ch);
}
string get_word(istream&is)
{
	skip_until_letter(is);
	string word;
	char ch{};
	while (is.get(ch) && (iswalnum(ch) || ch=='+'))// '+' for the "c++" word
		word += tolower(ch);
	is.putback(ch);
	return word;
}
int main()
try {
	map<string, int> words;

	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "No file" };

	istream& is{ ifs };

	while (is)
	{
		string s = get_word(is);
		if (s.size())
			++words[s];
	}

	//exercise 3
	vector<pair<int,const string*>> counts;
	counts.reserve(words.size());
	for (const auto& [word, count] : words) counts.push_back(pair<int,const string*>{count, &word});
	ranges::sort(counts,
		[](const pair<int, const string*>& one, const pair<int, const string*>& other)
		{return one.first < other.first;
		});
	for (const auto& [count,word] : counts)
		cout << count << ": " << *word << '\n';

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
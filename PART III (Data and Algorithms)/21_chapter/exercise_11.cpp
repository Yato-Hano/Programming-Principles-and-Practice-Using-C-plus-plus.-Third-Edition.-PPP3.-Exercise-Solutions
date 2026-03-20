/*
[11]
Write a program to ‘‘clean up’’ a text file for use in a word query program; that is, replace
punctuation with whitespace, put words into lowercase, replace don’t with do not (etc.), and
remove plurals (e.g., ships becomes ship). Don’t be too ambitious. For example, it is hard to
determine plurals in general, so just remove an s if you find both ship and ships. Use that
program on a real-world text file with at least 5000 words (e.g., a research paper).
*/

import PPP;
using namespace std;

string get_lowered_word(istream& is)
{
	char ch{};
	string word;
	while (is.get(ch) && (iswalpha(ch) || ch == '-' || ch == '\''))word += tolower(ch);
	is.putback(ch);
	return word;
}
string replace_word(const string &word)
{
	static vector<pair<string, string>> equivalence_table{ {"don't","do not"},
															{"can't","cannot"} };
	for (const pair<string, string>& p : equivalence_table) if (p.first == word) return p.second;
	return word;
}
vector<string> extract_words(istream& is)
{
	vector<string> words;
	for (char ch{}; is.get(ch);)
	{
		if (iswalpha(ch))
		{
			is.putback(ch);
			words.push_back(replace_word(get_lowered_word(is)));
		}
	}
	// remove plurals
	for(string& word_s:words)
	{
		if(word_s.back()=='s'&& 3< word_s.size()) // don't touch words like "as" or "its"
		{
			string word_no_s = word_s;
			word_no_s.pop_back();

			if (auto a = find(words.begin(), words.end(), word_no_s); a != words.end())
				word_s.pop_back();
		}
	}
	return words;
}
void extract_words_file()
{
	ifstream ifs{ "data.txt" };
	if (!ifs) throw exception{ "No file" };
	ofstream ofs{ "data_out.txt" };
	ranges::copy(extract_words(ifs), ostream_iterator<string>{ofs, " "});
}
int main()
try {
	extract_words_file();
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
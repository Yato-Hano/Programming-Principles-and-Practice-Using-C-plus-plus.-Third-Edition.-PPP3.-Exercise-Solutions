/*
[8]
Define a function that counts the number of characters in a Document.
[9]
Define a program that counts the number of words in a Document. Provide two versions: one
that defines word as ‘‘a whitespace-separated sequence of characters’’ and one that defines
word as ‘‘a sequence of consecutive alphabetic characters.’’ For example, with the former
definition, alpha.numeric and as12b are both single words, whereas with the second definition
they are both two words.
[10]
Define a version of the word-counting program where the user can specify the set of white-
space characters.
*/

import PPP;
using namespace std;

using Line = vector<char>;
class Text_iterator {
	list<Line>::iterator ln;
	Line::iterator pos;
public:
	using value_type = char;
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		:ln{ ll }, pos{ pp } {
	}
	list<Line>::iterator get_line()const { return ln; }
	Line::iterator  get_pos()const { return pos; }

	char& operator*() { return *pos; }
	Text_iterator& operator++();
	bool operator==(const Text_iterator& other) const
	{
		return ln == other.ln && pos == other.pos;
	}
	bool operator!=(const Text_iterator& other) const
	{
		return !(*this == other);
	}
};
struct Document {
	list<Line> line;
	Document() { line.push_back(Line{}); }
	using iterator = Text_iterator;
	Text_iterator begin()
	{
		return Text_iterator{ line.begin(), line.begin()->begin() };
	}
	Text_iterator end()
	{
		auto last = line.end();
		--last;
		return Text_iterator{ last, (*last).end() };
	}
};
istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch); )
	{
		d.line.back().push_back(ch); // add the character
		if (ch == '\n')
			d.line.push_back(Line{}); // add another line
	}
	if (d.line.back().size())
		d.line.push_back(Line{});
	// add final empty line
	return is;
}
Text_iterator& Text_iterator::operator++()
{
	++pos;
	// proceed to next character
	if (pos == ln->end())
	{
		++ln;
		// proceed to next line
		pos = ln->begin();
		// bad if ln==line.end(); so make sure it isn’t
	}
	return *this;
}
void print(Document& d)
{
	for (auto p : d)
		cout << p;
}

template<typename T>
size_t number_of_elements( T& container)
{
	size_t number{ 0 };
	for (auto a : container) ++number;
	return number;
}

template<typename T>
size_t number_of_whiteseparatad_words(T& container)
{
	size_t count{ 0 };
	bool in_word{ false };
	for (char ch : container)
	{
		if (iswspace(ch)) in_word = false;
		else 
			if (!in_word) 
		{
			++count;
			in_word = true;
		}
	}
	return count;
}

template<typename T>
size_t number_of_words(T& container)
{
	size_t count{ 0 };
	bool in_word{ false };
	for (char ch : container)
	{
		if (isalpha(ch))
		{
			if (!in_word)
			{
				++count;
				in_word = true;
			}
		}
		else in_word = false;
		
	}
	return count;
}
bool is_user_ws(char c, const string& whitespases)
{
	return whitespases.find(c) !=string::npos;
}
template<typename T>
size_t number_of_words_user_ws(T& container,const string & whitespases)
{
	size_t count{ 0 };
	bool in_word{ false };
	for (char ch : container)
	{
		if (is_user_ws(ch, whitespases)) in_word = false;
		else
			if (!in_word)
			{
				++count;
				in_word = true;
			}
	}
	return count;
}
int main()
try {
	Document d;
	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "No file" };
	ifs >> d;
	cout << "number_of_words: " << number_of_words(d) << '\n';
	cout << "number_of_whiteseparatad_words: " << number_of_whiteseparatad_words(d) << '\n';
	cout << "number_of_words_user_ws: " << number_of_words_user_ws(d," .1234567890") << '\n';
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
/*
[6]
Write a program that replaces punctuation with whitespace. Consider . (dot), ; (semicolon), ,
(comma), ? (question mark), − (dash), ’ (single quote) punctuation characters. Don’t modify
characters within a pair of double quotes ("). For example, ‘‘ − don’t use the as−if rule.’’
becomes ‘‘ don t use the as if rule ’’.
*/

import PPP;
using namespace std;

bool is_punct(char c)
{
	switch (c)
	{
		case '.':
		case ';':
		case ',':
		case '?':
		case '-':
		case '\'':
			return true;
		default:
			return false;
	}
}

int find_(const string& sequence,int position,const char& char_to_find)
{
	while (position< sequence.size()) {
		if (sequence[position] == char_to_find) return position;
		++position;
	}
	return -1; 
}


int add_until(const string& text, string& new_text, int position,const char &terminator)
{ // dont add terminator
	while (position < text.size()) {
		if (text[position] == terminator) return position;
		new_text += text[position];
		++position;
	}
	return -1;
}
string remove_punct(const string& text) // messy code
{
	string new_text;
	for (size_t pos = 0; pos < text.size(); pos++)
	{
		if (is_punct(text[pos])) 
		{
			new_text += ' ';
		}
		else 
		if (text[pos] == '"') // don't change within ""
		{
			int next_quote{ find_(text, (pos + 1), '"') };
			if (next_quote != -1) 
			{
				new_text += text[pos];
				pos = add_until(text, new_text, pos+1, '"');//new position
				if (pos == -1) // not found
					throw string{ "Bad termination of add_until()" };

				new_text += text[pos];
			}
			else new_text += text[pos];
		}
		else	
		new_text += text[pos];
	}
	return new_text;
}

int main()
try {
	ifstream ifs{ "t.txt" };
	if (!ifs) throw exception{ "Noo file" };

	string text;
	getline(ifs, text);

	string text_without_punct;
	text_without_punct=remove_punct(text);

	cout << text_without_punct<<'\n';

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


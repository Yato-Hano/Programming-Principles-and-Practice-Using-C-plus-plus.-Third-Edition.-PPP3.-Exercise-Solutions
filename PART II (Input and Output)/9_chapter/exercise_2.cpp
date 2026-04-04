/*
[2]
Write a program that given a file name and a word will output each line that contains that
word together with the line number. Hint: getline().
*/

import PPP;
using namespace std;

void to_lower(string& word)
{
	for (char& letter : word)
	{
		letter = tolower(letter);
	}
}
string get_word(istream&is)
{
	char ch{};
	while (is.get(ch) && !iswalpha(ch));
	is.putback(ch);

	string word;

	while (is.get(ch) && iswalpha(ch))word+=ch;
	is.putback(ch);
	return word;
}
bool is_there_word(const string& text, const string& word_to_find)
{
	istringstream is{ text };

	for (string s; is;)
	{
		s= get_word(is);
		to_lower(s);
		if (s == word_to_find) return true;
	}
	return false;
}

int main()
try {
	string word,file_name;

	cout << "Enter a fle name: ";
	cin >> file_name;
	ifstream ifs{ file_name };
	if (!ifs) throw string{ "Can't open file" };

	cout << "Enter a word to find: ";
	cin >> word;
	to_lower(word);

	string line;
	for (size_t i = 1; getline(ifs, line); i++)
	{
		
		if (is_there_word(line, word))cout << i << ". " << line << '\n';
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
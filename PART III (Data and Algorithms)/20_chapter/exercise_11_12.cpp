/*
[11] 
Build a map of (English word, Spanish word) pairs of words with equivalent meaning. Each
word is a string. Read the pairs from a file, and display them on the screen. A couple of
dozen pairs will do. Give a user the choice of displaying the words in English lexicographi-
cal order or Spanish lexicographical order.
[12]
Repeat the previous exercise, but handle cases where a word has more than one meaning.
For example, (sheet,hoja) and (leaf,hoja). Hint: multimap.
*/

import PPP;
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
using namespace std;

vector<pair<wstring, wstring>> get_words()
{
	wifstream ifs{ "data.txt" }; //file in UTF-8
	if (!ifs) throw exception{ "No file" };
	ifs.imbue(std::locale(".utf8"));

	vector<pair<wstring, wstring>> words_data;

	for (pair<wstring, wstring> word_pair; ifs >> word_pair.first >> word_pair.second;)
		words_data.push_back(word_pair);

	return words_data;
}
template<class T,class B>
void print_map(const map<T, B>& m)
{
	for (const auto& [f, s] : m)
		wcout << f <<": " <<s << '\n';
}

// for exercise 12
void print_map_eq_r(const multimap<wstring, wstring>& m)
//output: hoja: - sheet - leaf
{
	for (auto f = m.begin(); f != m.end(); ) {

		auto range = m.equal_range(f->first);

		wcout << f->first << ": ";
		for (f = range.first; f != range.second; ++f) 
			wcout << " - " << f->second;
		
		wcout << '\n';
	}
}
int main()
try {

	if (int result = _setmode(_fileno(stdout), _O_U16TEXT); result == -1) //also, console font is Consolas (standard)
	{
		perror("Cannot set mode");
		return 1;
	}
	vector<pair< wstring, wstring>> words_data{ get_words() };
	
	multimap< wstring,  wstring> eng_sorting;
	multimap < wstring,   wstring> sp_sorting;

	for (const pair< wstring, wstring>& p : words_data)
	{
		eng_sorting.emplace(p.first, p.second);
		sp_sorting.emplace(p.second, p.first);
	}
	
	while (wcin)
	{
		wcout << "To sort by English words-e. To sort by Spanish words-s: ";
		wchar_t sellection{};
		wcin >> sellection;
		switch (sellection)
		{
		case 'e':
			print_map_eq_r(eng_sorting);
			break;
		case 's':
			print_map_eq_r(sp_sorting);
			break;
		default:
			wcout << "Try e or s.\n" ;
			break;
		}
		wcout << '\n';
	}

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
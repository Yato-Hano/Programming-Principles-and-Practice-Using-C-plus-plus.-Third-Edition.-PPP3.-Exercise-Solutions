/*
[12]
Write a program (using the output from the previous exercise) to answer questions such as:
‘‘How many occurrences of ship are there in a file?’’ ‘‘Which word occurs most frequently?’’
‘‘Which is the longest word in the file?’’ ‘‘Which is the shortest?’’ ‘‘List all words starting
with s.’’ ‘‘List all four-letter words.’
[13]
Provide a GUI for the program from the previous exercise.
*/

#include "PPP/GUI.h"
#include <map>
using namespace Graph_lib;

size_t occurrences_number(vector<string> words, const string& word_to_find)
{
	ranges::sort(words);
	auto result=ranges::equal_range(words, word_to_find);
	return result.size();
}
string max_occurrences_word(const vector<string>& words)
{
	map<string, size_t> m;
	for (const string& s : words) m[s]++;

	string max_word;
	size_t max_number{ 0 };
	for (const auto& [word, number] : m) 
	{
		if (max_number < number)
		{
			max_word = word;
			max_number = number;
		}
	}
	return max_word;
}
string shortest_word(vector<string> words)
{
	ranges::sort(words, [](const string& s1, const string& s2) {return s1.size() < s2.size(); });
	return words.front();
}
string longest_word(vector<string> words)
{
	ranges::sort(words, [](const string& s1, const string& s2) {return s1.size() < s2.size(); });
	return words.back();
}
vector<string> words_starting_with(const vector<string>& words, char ch)
{
	vector<string> v;
	for (const string& s : words)if (s.front() == ch)v.push_back(s);
	return v;
}
vector<string> words_of_length(const vector<string>& words, int length)
{
	vector<string> v;
	for (const string& s : words)if (s.length() == length) v.push_back(s);
	return v;
}
//--------------------------------------

struct My_Out_box : Shape {//handles newline
	My_Out_box(Point p) { Shape::add(p); }

	void put(const string& s)
	{
		text_lines.clear();
		istringstream is{ s };
		for (string i; getline(is, i);)
			text_lines.push_back(i);
		redraw();
	}
	void put(const vector<string>& s)
	{
		text_lines = s;
		redraw();
	}
	void clear() { text_lines.clear(); redraw(); }
	void draw_specifics(Painter& painter) const override;
private:
	vector<string> text_lines;
};
void My_Out_box::draw_specifics(Painter& painter) const
{
	Vector_ref<const Text> texts;
	for (const string& s : text_lines)
		texts.push_back(make_unique<Text>(Point{ 0,0 }, s));
	painter.draw_text_column(point(0), texts);
}

class Words_Window :public Window
{
public:
	Words_Window(Application&, const string&);
private:
	Application* app;
	//----
	ifstream input_file;
	vector<string> words;
	//----
	Button print_max_occurrences_word;
	Button print_longest_word;
	Button print_shortest_word;

	In_box print_occurrences_number;  // string
	In_box print_words_starting_with;// char
	In_box print_words_of_length;// int
	//----
	My_Out_box text_box;
	Button quit;
	//----
	void open_input_file_read(const string& name);
	//----
	void print_occurrences_number_cb();
	void print_words_of_length_cb();
	void print_words_starting_with_cb();
};
void Words_Window::open_input_file_read(const string& name)
{
	input_file.open(name);
	if (!input_file)
		text_box.put("Cannot open the input file.");
	else
	{
		for (string word; input_file>>word;) words.push_back(word);
		text_box.put("Opened the input file.");
	}
}
void Words_Window::print_words_of_length_cb()
{
	string maybe_number = print_words_of_length.last_string_value();
	istringstream is{ maybe_number };
	if (size_t number{ 0 };is>> number)
	{
		text_box.put(words_of_length(words,number ));
	}
	else
	{
		text_box.put("Error: Enter a number.");
	}
}
void Words_Window::print_words_starting_with_cb()
{
	string letter = print_words_starting_with.last_string_value();
	if (letter.length() == 1)
	{
		text_box.put(words_starting_with(words, letter.front()));
	}
	else
	{
		text_box.put("Error: Enter one letter.");
	}
}
void Words_Window::print_occurrences_number_cb()
{
	size_t number = occurrences_number(words, print_occurrences_number.last_string_value());
	ostringstream os;
	os << number;
	text_box.put(os.str());
}
Words_Window::Words_Window(Application& a, const string& file_name)
	:Window{ 1200,1000,"Words Window" }
	, app{ &a }
, print_max_occurrences_word{ {0,0},70,20,"Print word with max occurrences",[this] {text_box.put(max_occurrences_word(words));	} }
	, print_longest_word{ {0,30},70,20,"Print longest word",[this] {text_box.put(longest_word(words)); } }
	, print_shortest_word{ {0,60},70,20,"Print shortest word",[this] {text_box.put(shortest_word(words)); } }

	, print_occurrences_number{ {0,90},70,20,"Print number of occurrences:",[this] {print_occurrences_number_cb(); } }
	, print_words_starting_with{ {0,130},70,20,"Print words starting with:",[this] {print_words_starting_with_cb(); } }
	, print_words_of_length{ {0,170},70,20,"Print words of length:",[this] {print_words_of_length_cb(); } }
 
	, text_box{ {250,0} }
	, quit{ {x_max() - 70,0},70,20,"Quit",[this] {close(); app->quit(); } }
{
	open_input_file_read(file_name);
	attach(print_max_occurrences_word);
	attach(print_longest_word);
	attach(print_shortest_word);
	attach(print_occurrences_number);
	attach(print_words_starting_with);
	attach(print_words_of_length);

	print_words_of_length.hide_buttons();
	print_words_of_length.show();
	print_words_starting_with.hide_buttons();
	print_words_starting_with.show();
	print_occurrences_number.hide_buttons();
	print_occurrences_number.show();

	attach(quit);
	attach(text_box);
}


int main(int /*argc*/, char* /*argv*/[])
try {
	Application app;
	Words_Window win{ app,"words.txt"};
	app.gui_main();
}
catch (exception& e)
{
	ofstream ofs{ "errors.txt" };
	ofs << e.what() << '.' << endl;
}
catch (...)
{
	ofstream ofs{ "errors.txt" };
	ofs << "Some error." << endl;
}
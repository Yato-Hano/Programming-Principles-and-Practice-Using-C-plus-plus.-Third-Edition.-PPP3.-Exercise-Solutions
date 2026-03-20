/*
[6]
Write a find-and-replace operation for Documents based on §19.5.
*/

/*
implemented:
	Document::erase()
	Document::insert()
	find_and_replace()
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

	Text_iterator erase(Text_iterator);
	Text_iterator insert(Text_iterator,char);

	Text_iterator begin()
	{
		return Text_iterator{ line.begin(), line.begin()-> begin() };
	}
	Text_iterator end()
	{
		auto last = line.end();
		--last;
		return Text_iterator{ last, (*last).end() };
	}
};
Text_iterator Document::insert(Text_iterator ti, char ch)
{
	if (ti == end())return ti;

	list<Line>::iterator current_line = ti.get_line();
	list<Line>::iterator next_line = current_line;
	++next_line;

	Line::iterator inserted_pos = current_line->insert(ti.get_pos(), ch);
	Line::iterator next_pos = inserted_pos;
	++next_pos;

	if (ch == '\n')
	{
		line.insert(next_line, Line{ next_pos ,current_line ->end()});
		current_line->erase(next_pos, current_line->end());
	}
	return Text_iterator{ current_line ,inserted_pos };
}
Text_iterator Document::erase(Text_iterator ti)
// options: erased char in a line.erased'\n' in a line.erased last char in a line.
{
	if (ti == end())return ti;
	char erased_simbol{ *ti };
	list<Line>::iterator current_line = ti.get_line();
	Line::iterator ersd_pos= current_line->erase(ti.get_pos());
	if (current_line->empty())// the line has become empty(erased last char, probably a '\n')
	{
		list<Line>::iterator it=line.erase(current_line);
		return Text_iterator{ it,it->begin()};
	}

	list<Line>::iterator next_line =current_line;
	++next_line;

	if (erased_simbol == '\n'
		&&!next_line->empty())//next line is the last one
	{
		//merging the current and the next lines
		ersd_pos = current_line->insert_range(current_line->end(), *next_line);
		line.erase(next_line);
	}
	return Text_iterator{ current_line,ersd_pos };
}
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
	if (pos == ln-> end()) 
	{
		++ln;
		// proceed to next line
		pos = ln-> begin();
		// bad if ln==line.end(); so make sure it isn’t
	}
	return *this;
}
void print(Document & d)
{
	for (auto p:d)
			cout << p;
}
void print_lines(Document& d)
{
	auto it = d.line.begin();
	for (size_t i = 0; i < d.line.size(); i++,++it)
	{
		cout << '{' << i << "}";
		for (char ch : *it)
			cout << ch;
	}
	cout << '\n';
}
template<typename Iter>
	requires bidirectional_iterator<Iter>
void advance(Iter& p, int n)
{
	while (0 < n)
	{
		++p;
		--n;
	}
	while (n < 0)
	{
		--p;
		++n;
	}
}
template<typename Iter>
	//requires forward_iterator<Iter>
bool match(Iter f, Iter l, const string s)
// does f-l start with s
{
	if (s.empty())return false;
	auto s_it = s.begin();
	while (s_it != s.end() && f != l)
	{
		if (*s_it != *f) return false;
		++f;
		++s_it;
	}
	return s_it == s.end();
}

template<typename Iter>
	requires forward_iterator<Iter>
Iter match_iter(Iter f, Iter l, const string s)
// does f-l start with s
{
	if (s.empty())return l;
	auto s_it = s.begin();
	while (s_it != s.end() && f != l)
	{
		if (*s_it != *f) return l;
		++f;
		++s_it;
	}
	if (s_it == s.end()) return f;
	return l;
}
Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
// find s in [first:last)
{
	if (s.size() == 0)
		// can’t find an empty string
		return last;
	char first_char = s[0];
	auto p = last;
	for (p = find(first, last, first_char)
		;
		!(p == last || match(p, last, s));
		++p)	;// do nothing
	return p;
}

void find_and_replace(Document& doc, const string& from, const string& to)
{
	if (from.empty())return;
	Text_iterator current = doc.begin();

	while (true)
	{
		Text_iterator pos = find_txt(current, doc.end(), from);
		if (pos == doc.end()) return;

		for (int i = 0; i < from.size(); i++)
			pos = doc.erase(pos);

		for (char ch : to)
		{
			pos = doc.insert(pos, ch);
			++pos;
		}
		current = pos;
	}
}

void test(Document& d, const string& from, const string& to)
{
	cout << "\nLines before: " << d.line.size() << '\n';
	print_lines(d);
	find_and_replace(d, from, to);
	cout << "\nLines after: " << d.line.size() << '\n';
	print_lines(d);
}
int main()
try {
	Document d;
	ifstream ifs{ "data.txt" };
	if (!ifs)throw exception{ "No file" };
	ifs >> d;

	//test(d, "2", "two"); //success
//	test(d, "\n", "|");//success
	//test(d, "123\n4", "");//success
//	test(d, "123\n4", "A");//success
	//test(d, "123", "line");//success
	//test(d, "123\n", "line\n");//success

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
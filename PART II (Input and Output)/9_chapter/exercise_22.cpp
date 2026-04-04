/*
[22]
Make a version of the calculator from Chapter 6 that accepts Roman numerals rather than the
usual Arabic ones, for example, XXI + CIV == CXXV.
*/

/*
	// a simple expression grammar :
Calculation:
	Statement
	Print
	Quit
	Calculation Statement
Statement:
	Declaration
	Expression
Declaration:
	"let" Name "=" Expression
Expression:
	Term
	Expression "+" Term
	Expression "−" Term
Term :
	Primary
	Term "∗" Primary
	Term "/" Primary
	Term "%" Primary
Primary :
	Number
	pow "(" Expression "," Expression ")" // only int for the second operand
	sqrt "(" Expression ")"  //  only int
	sin "(" Expression ")"
	"(" Expression ")"
Number :
	Roman_int literal
*/


import PPP;
using namespace std;


inline bool is_there(char ch, const string& w)
{
	for (char c : w)if (ch == c)return true;
	return false;
}

bool is_valid(const string& s)
{
	for (char ch : s)if (!is_there(ch, "IVXLCDM"))return false;
	return true;
}

unsigned int roman_to_int(const string& s)
{
	map<char, int> roman;
	roman['I'] = 1;
	roman['V'] = 5;
	roman['X'] = 10;
	roman['L'] = 50;
	roman['C'] = 100;
	roman['D'] = 500;
	roman['M'] = 1000;

	unsigned int total = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (i < s.size() - 1 && roman[s[i]] < roman[s[i + 1]]) {
			total -= roman[s[i]];
		}
		else {
			total += roman[s[i]];
		}
	}
	return total;
}

string int_to_roman(unsigned int n)
{
	vector<int> values{ 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	vector<string> symbols{ "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

	string result = "";

	for (int i = 0; i < symbols.size(); ++i)
	{
		while (n >= values[i])
		{
			result += symbols[i];
			n -= values[i];
		}
	}
	return result;
}

class Roman_int {
public:
	Roman_int(string val);
	Roman_int(unsigned int val);
	const unsigned int& as_int() const { return value; }
	const string& as_roman() const { return roman_number; }
private:
	string roman_number;
	unsigned int value{ 0 };
};
Roman_int::Roman_int(string val)
	:value{ roman_to_int(val) }, roman_number{ val }
{
	if (!is_valid(val)) throw exception{ "Roman_int: bad literal" };
}
Roman_int::Roman_int(unsigned int val)
	:value{ val }, roman_number{ int_to_roman(val) }
{
}
ostream& operator<<(ostream& os, const Roman_int& r)
{
	return os << r.as_roman();
}
istream& operator>>(istream& is, Roman_int& r)
{
	string s;
	is >> s;
	r = Roman_int{ s };
	return is;
}

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) {} // token represents itself
	Token(char ch, double val) :kind(ch), value(val) {} // numbers
	Token(char ch, string val) :kind(ch), name(val) {} // variables
};
struct Variable {
	string name;
	double value;
	bool is_const;
	Variable(string n, double v) :name(n), value(v), is_const(false) {}
	Variable(string n, double v, bool c) :name(n), value(v), is_const(c) {}
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) {}
	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char); // ignore utill char argument
};

class Symbol_table {
public:
	vector<Variable> names;
	double assign(string name); // name = expression()
	double declare(); // name = expression()
	double get(string s);
	void set(string s, double d); // set variable
	bool is_declared(string s);
};

Symbol_table st;
Token_stream ts;

constexpr char let = '#'; // declaration
constexpr char sin_ = 'S';
constexpr char help_ = 'h';
constexpr char Help_ = 'H';
constexpr char assign_ = '=';
constexpr char sqrt_ = 's';
constexpr char pow_ = 'p';
constexpr char name_ = 'a';
constexpr char quit_ = 'Q';
constexpr char print_ = '\n';
constexpr char number = '8'; // ndicates  numbers

const string quit = "quit";
const string help = "help";
const string prompt = "> ";
const string result = "= ";

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch{ ' ' };
	while (ch == ' ') cin.get(ch);

	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case assign_:
	case quit_:
	case print_:
	case let:
	case ',': // for pow(x,i)
		return Token(ch);
	case 'I':
	case 'V':
	case 'X':
	case 'L':
	case 'C':
	case 'D':
	case 'M':
	{
		cin.unget();
		Roman_int val{""};
		cin >> val;
		return Token(number, val.as_int());
	}
	default:
		if (isalpha(ch) || ch == '_') { // variable starts with a lettter and contains letters and digits
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.unget();
			if (s == quit) return Token(quit_);
			if (s == help) return Token(help_);
			if (s == "sin") return Token(sin_);
			if (s == "pow") return Token(pow_);
			if (s == "sqrt") return Token(sqrt_);
			return Token(name_, s);
		}
		PPP::error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin.get(ch))
		if (ch == c) return;
}


double Symbol_table::get(string s)  // get variable
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) return st.names[i].value;
	PPP::error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d) // set variable
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) {
			if (st.names[i].is_const) PPP::error("set: assignment to const ", s);
			st.names[i].value = d;
			return;
		}
	PPP::error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) return true;
	return false;
}


double expression();

double primary() // deals with ( ), sin, pow, sqrt, variables and numbers
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		int d = PPP::narrow<int>(expression());
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return d;
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case sqrt_:
	{
		t = ts.get();
		if (t.kind != '(') PPP::error("'(' expected");
		int d = PPP::narrow<int>(expression());
		if (d < 0)PPP::error("negative argument for sqrt");
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return sqrt(d);
	}
	case sin_:
	{
		t = ts.get();

		if (t.kind != '(') {
			ts.unget(t);
			PPP::error("'(' expected");
		}
		int d = PPP::narrow<int>(expression());
		t = ts.get();
		if (t.kind != ')') {
			ts.unget(t);
			PPP::error("')' expected");
		}
		return sin(d);
	}
	case pow_:
	{
		t = ts.get();
		if (t.kind != '(') PPP::error("'(' expected");
		int x = PPP::narrow<int>(expression());
		t = ts.get();
		if (t.kind != ',') PPP::error("',' expected");
		int i = PPP::narrow<int>(expression());
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return pow(x, i);
	}
	case number:
		return PPP::narrow<int>(t.value);
	case Help_: case help_:
		ts.unget(t);
		return 0; // no number to return
	case print_:
		ts.unget(t);
		return 0;// no number to return
	case name_:
	{
		string name = t.name;
		t = ts.get();
		if (t.kind == assign_) return st.assign(name);
		ts.unget(t);
		return st.get(name);
	}
	default:
		PPP::error("primary expected");
	}
}

double term()// deals with * /
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) PPP::error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression() // deals with + -
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double Symbol_table::declare() // name = expression()
// assume we already have seen let
{
	Token t = ts.get();
	if (t.kind != name_) PPP::error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) PPP::error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != assign_) PPP::error("= missing in declaration of ", name);
	double d = expression();
	st.names.push_back(Variable(name, d));
	return d;
}
double Symbol_table::assign(string name) // name = expression()
// wealready have seen name =
{
	double d = expression();
	set(name, d);
	return d;
}
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return st.declare();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print_);
}

void guide()
{
	cout << "Welcome to our simple calculator. Please enter expressions using integer numbers.\n"
		<< "Operators *, /, -, +, sqrt(x), pow(x,i), sin(x) are available.\n"
		<< "Enter for print, " << quit << " for closing the pogram.\n";
}

void calculate()
{
	while (true)
		try
		{
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print_) t = ts.get();
			if (t.kind == Help_ || t.kind == help_)
			{
				guide();
				t = ts.get();
			}
			if (t.kind == quit_) return;
			ts.unget(t);
			Roman_int r{ unsigned (statement())};
			cout << result << r << endl;
		}
		catch (PPP::narrowing_error& e) {
			cerr << "Please, use integers only." << endl;
			clean_up_mess();
		}
		catch (runtime_error& e) {
			cerr << e.what() << endl;
			clean_up_mess();
		}
		catch (exception& e) {
			cerr << "exception: " << e.what() << endl;
			clean_up_mess();
		}
}


int main()
try {
	st.names.push_back(Variable{ "pi",3.14159265358979323846,true });
	st.names.push_back(Variable{ "k",1000 });
	calculate();
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

/*
[25] 
Add a command from x to the calculator from Chapter 6 that makes it take input from a file x.
Add a command to y to the calculator that makes it write its output (both standard output and
error output) to file y. Write a collection of test cases based on ideas from §6.3 and use that
to test the calculator. Discuss how you would use these commands for testing.
*/

// solutions for the 
// exercise are set_input_stream() and set_output_stream() functions at the very bottom.

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
	floating−point−literal
*/


import PPP;
using namespace std;


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
	istream& is;
public:
	Token_stream(istream& s) :is{ s }, full(0), buffer(0) {}
	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char); // ignore utill char argument
};

class Symbol_table {
public:
	vector<Variable> names;
	double assign(Token_stream& ts,string name); // name = expression()
	double declare(Token_stream& ); // name = expression()
	double get(string s);
	void set(string s, double d); // set variable
	bool is_declared(string s);
};

Symbol_table st;

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
	while (ch == ' ') is.get(ch);

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
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		is.unget();
		double val;
		is >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == '_') { // variable starts with a lettter and contains letters and digits
			string s;
			s += ch;
			while (is.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			is.unget();
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
	while (is.get(ch))
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


double expression(Token_stream&);

double primary(Token_stream& ts) // deals with ( ), sin, pow, sqrt, variables and numbers
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return d;
	}
	case '-':
		return -primary(ts);
	case '+':
		return primary(ts);
	case sqrt_:
	{
		t = ts.get();
		if (t.kind != '(') PPP::error("'(' expected");
		double d = expression(ts);
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
		double d = expression(ts);
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
		double x = expression(ts);
		t = ts.get();
		if (t.kind != ',') PPP::error("',' expected");
		int i = PPP::narrow<int>(expression(ts));
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return pow(x, i);
	}
	case number:
		return t.value;
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
		if (t.kind == assign_) return st.assign(ts,name);
		ts.unget(t);
		return st.get(name);
	}
	default:
		PPP::error("primary expected");
	}
}

double term(Token_stream& ts)// deals with * /
{
	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary(ts);
			break;
		case '/':
		{
			double d = primary(ts);
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

double expression(Token_stream& ts) // deals with + -
{
	double left = term(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term(ts);
			break;
		case '-':
			left -= term(ts);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double Symbol_table::declare(Token_stream& ts) // name = expression()
// assume we already have seen let
{
	Token t = ts.get();
	if (t.kind != name_) PPP::error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) PPP::error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != assign_) PPP::error("= missing in declaration of ", name);
	double d = expression(ts);
	st.names.push_back(Variable(name, d));
	return d;
}
double Symbol_table::assign(Token_stream& ts,string name) // name = expression()
// wealready have seen name =
{
	double d = expression(ts);
	set(name, d);
	return d;
}
double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return st.declare(ts);
	default:
		ts.unget(t);
		return expression(ts);
	}
}

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print_);
}

void guide(ostream& os)
{
	os << "Welcome to our simple calculator. Please enter expressions using floating−point numbers.\n"
		<< "Operators *, /, -, +, sqrt(x), pow(x,i), sin(x) are available\n"
		<< "Enter for print, " << quit << " for closing the pogram.\n";
}

void calculate(Token_stream& ts, ostream& os)
{
	while (true)
		try
		{
			os << prompt;
			Token t = ts.get();
			while (t.kind == print_) t = ts.get();
			if (t.kind == Help_ || t.kind == help_)
			{
				guide(os);
				t = ts.get();
			}
			if (t.kind == quit_) return;
			ts.unget(t);
			os << result << statement(ts) << endl;
		}
		catch (exception& e) {
			os << "exception: " << e.what() << endl;
			clean_up_mess(ts);
		}
		catch (runtime_error& e) {
			os << e.what() << endl;
			clean_up_mess(ts);
		}
}
istream& set_input_stream()
{
	string file_name_in;
	cout << "Type input file name or cin: ";
	cin >> file_name_in;
	if (file_name_in == "cin")
	{
		return cin;	
	}
	else
	{
		static ifstream ifs{ file_name_in };
		if (!ifs) throw exception{ "No file" };
		return ifs;
	}

}
ostream& set_output_stream()
{
	string  file_name_out;
	cout << "Type output file name or cout: ";
	cin >> file_name_out;
	if (file_name_out == "cout")
	{
		return cout;
	}
	else
	{
		static ofstream ofs{ file_name_out };
		if (!ofs) throw exception{ "No file" };
		return ofs;
	}
}

int main()
try 
{
	st.names.push_back(Variable{ "pi",3.14159265358979323846,true });
	st.names.push_back(Variable{ "k",1000 });
	
	Token_stream ts{ set_input_stream() };
	calculate(ts, set_output_stream());
	
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

/*

	//messy solution for files

	string file_name_in, file_name_out;
	cout<< "Type input file name or cin: ";
	cin >> file_name_in;
	cout << "Type output file name or cout: ";
	cin >> file_name_out;

	if(file_name_in =="cin")
	{
		if (file_name_out == "cout")
		{ // cin cout
			Token_stream ts{ cin };
			calculate(ts, cout);
		}
		else
		{ // cin file
			ofstream ofs{ file_name_out };
			if (!ofs) throw exception{ "No file" };

			Token_stream ts{ cin };
			calculate(ts, ofs);
		}
	}
	else
	{
		if (file_name_out == "cout")
		{ // file cout
			ifstream ifs{ file_name_in };
			if (!ifs) throw exception{ "No file" };

			Token_stream ts{ ifs };
			calculate(ts, cout);
		}
		else
		{// file file
			ifstream ifs{ file_name_in };
			if (!ifs) throw exception{ "No file" };

			ofstream ofs{ file_name_out };
			if (!ofs) throw exception{ "No file" };

			Token_stream ts{ ifs };
			calculate(ts, ofs);
		}
	}
*/
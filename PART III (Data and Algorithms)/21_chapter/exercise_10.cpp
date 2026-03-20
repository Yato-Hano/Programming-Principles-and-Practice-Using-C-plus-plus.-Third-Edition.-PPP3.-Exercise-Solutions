/*
[10]
Provide a GUI interface for querying a file of Orders; e.g., ‘‘Find all orders from Joe,’’ ‘‘Find
the total value of orders in file Hardware,’’ and ‘‘List all orders in file Clothing.’’ Hint: First
design a non-GUI interface; then, build the GUI on top of that.
*/

#include "PPP/GUI.h"
#include <numeric>
using namespace Graph_lib;

// after typing in a input box hit enter to send line to the program
/*
format:

for Order:
{ name, address, data, purchases }

for purchases (also for any vector):
{Purchase,Purchase,Purchase}

for Purchase:
{name,unit_price,count}

Order example: {name,adress,data,{{name1,12.0,1},{name2,12.3,3},{name3,12.1,13}}}
*/

string read_string_until(istream& is, const char terminator_ch)
{
	string word;
	char ch{};
	while (is.get(ch) && ch != terminator_ch)
		word += ch;
	if (ch != terminator_ch || !is)
		throw exception{ string("read_until(): expected " + terminator_ch).c_str() };
	return word;
}
//--------------------------------------
struct Purchase
{
	string name;//product
	double unit_price;
	int count;
};
ostream& operator<<(ostream& os, const Purchase& v)
{
	return os << "{ " << v.name << ", " << v.unit_price << ", " << v.count << " }";
}
istream& operator>>(istream& is, Purchase& v)
//{name,unit_price,count}
{
	if (char ch1{}; !(is >> ch1) || ch1 != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	v = {};

	v.name = read_string_until(is, ',');

	char ch3{}, ch4{};
	if (!(is >> v.unit_price >> ch3 >> v.count >> ch4))
		throw exception{ "Bad Purchase reading" };

	if (ch3 != ',')
		throw exception{ "Bad Purchase: ',' expected" };

	if (ch4 != '}')
		throw exception{ "Bad Purchase termination" };

	return is;
}

//--------------------------------------
template<ranges::range R>
istream& operator>>(istream& is, R& v)
{
	char ch{};
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	v.clear();
	for (ranges::range_value_t<R> val{}; is >> val; )
	{
		v.push_back(val);
		is >> ch;
		if (ch != ',')break;
	}
	if (ch == '}')
		return is;
	else
		throw exception{ "Bad range termination: expected }" };
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << "{ ";
	for (size_t i = 0; i < v.size(); i++)
	{
		os << v[i];
		if ((1 + i) < v.size())	os << ',';
		os << ' ';
	}
	os << '}';
	return os;
}
//--------------------------------------
struct Order
{
	string name;//costomer
	string address;
	string data;
	vector<Purchase> purchases;
};
ostream& operator<<(ostream& os, const Order& v)
{
	return os << "{ "
		<< v.name << ", "
		<< v.address << ", "
		<< v.data << ", "
		<< v.purchases
		<< " }";
}
istream& operator>>(istream& is, Order& v)
//{name,address,data,purchases}
{
	if (char ch1{}; !(is >> ch1) || ch1 != '{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}

	v = {};
	v.name = read_string_until(is, ',');
	v.address = read_string_until(is, ',');
	v.data = read_string_until(is, ',');

	if (!(is >> v.purchases)) // vector
		throw exception{ "Bad Purchase vector reading" };

	if (char ch2{}; !(is >> ch2) || ch2 != '}')
		throw exception{ "Bad Purchase termination" };

	return is;
}
//--------------------------------------
double unit_price(const Purchase& p)
{
	return p.unit_price * p.count;
}
double order_price(const Order& o)
{
	double sum{ 0 };
	for (const Purchase& p : o.purchases)
		sum += unit_price(p);
	return sum;
}

double orders_price(double init, const Order& o)
{
	return init + order_price(o);
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

class Orders_Window :public Window
{
public:
	Orders_Window(Application&);
private:
	Application* app;
	//----
	ifstream input_file;
	ofstream output_file;
	vector<Order> orders;
	//----
	In_box input_file_name_box;
	In_box output_file_name_box;
	//----
	Button total_price;
	Button find_by_name;
	In_box find_by_name_input_box;
	Button print_all;
	//----
	My_Out_box text_box;
	Button quit;
	//----
	void open_input_file();
	void open_output_file();
	void read_file();
	void sort_by_name_print();
	double calculate_price();
	//----
	bool is_there_any_data() {
		if (orders.empty()){
			text_box.put("No Orders located.");
			return false;
		}
		return true;
	}
	void show_changes_in_file_now() { output_file << endl; text_box.put("The operation is completed.");}
};

void Orders_Window::sort_by_name_print()
{
	if(is_there_any_data())
	{
		ranges::sort(orders, [](const Order& o1, const Order& o2) {return o1.name < o2.name; });
		string name_to_find{ find_by_name_input_box.last_string_value()};
		auto result = ranges::equal_range(orders, name_to_find, {}, &Order::name);
		if (result.empty())
		{
			text_box.put("Result range is empty.");
		}
		else
		{
			ranges::copy(result, ostream_iterator<Order>{output_file, "\n"});
			show_changes_in_file_now();
		}
	}
}
void Orders_Window::read_file()
{
	input_file.clear(ios::goodbit);
	try 
	{
		if (!(input_file >> orders))
			text_box.put("Failed file reading.");
		else 
			text_box.put("File reading is completed.");
	}
	catch (exception& err)
	{
		text_box.put(err.what());
	}
}
void Orders_Window::open_output_file()
{
	output_file.open(output_file_name_box.last_string_value(),ios::app);
	if (!output_file)
		text_box.put("Cannot open the output file.");
	else
		text_box.put("Opened the output file.");

}
void Orders_Window::open_input_file()
{
	input_file.open(input_file_name_box.last_string_value());
	if (!input_file)
		text_box.put("Cannot open the input file.");
	else 
		text_box.put("Opened the input file.");
}
double Orders_Window::calculate_price()
{
	return accumulate(orders.begin(), orders.end(), 0.0, orders_price);
}
Orders_Window::Orders_Window(Application& a)
	:Window{ 1000,600,"Orders Window" }
	, app{ &a }

, input_file_name_box{ {0,0},100,20,"Input file name:",[this] {open_input_file();	read_file(); } }
, output_file_name_box{ {0,50},100,20,"Output file name:",[this] {open_output_file(); } }

, total_price{ {0,100},70,20,"Total price",
[this] 	{ 		output_file << "Total price: " << calculate_price();  // it prints 0 to the file if there are no orders 
		show_changes_in_file_now(); 
		is_there_any_data(); //it prints in the Window
	}
}
, find_by_name{ {0,150},70,20,"Find by name",[this] { sort_by_name_print();	} }
, find_by_name_input_box{ {100,120},100,20,"Name:" }
, print_all{ {0,200},70,20,"Print all",[this] 
	{
		if (is_there_any_data()) 
		{
			ranges::copy(orders, ostream_iterator<Order>{output_file, "\n"});
			show_changes_in_file_now();
		}
	} }

, text_box{ {50,250} }
, quit{ {x_max() - 70,0},70,20,"Quit",[this] {close(); app->quit(); } }
{
	attach(quit);
	attach(total_price);
	attach(find_by_name);
	attach(find_by_name_input_box);
	attach(print_all);

	attach(text_box);
	attach(output_file_name_box);
	attach(input_file_name_box);
	input_file_name_box.hide_buttons();
	output_file_name_box.hide_buttons();
	find_by_name_input_box.hide_buttons();

	find_by_name_input_box.show();
	input_file_name_box.show();
	output_file_name_box.show();
}


int main()
try {
	Application app;
	Orders_Window win{ app };
	app.gui_main();
}
catch (exception& e)
{
	ofstream ofs{ "errors.txt" };
	ofs << e.what() << '.' << endl;
	return 1;
}
catch (...)
{
	ofstream ofs{ "errors.txt" };
	ofs << "Some error." << endl;
	return 2;
}
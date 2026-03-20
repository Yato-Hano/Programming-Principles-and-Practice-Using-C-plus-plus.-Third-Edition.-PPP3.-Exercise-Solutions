/*
[9]
Provide a GUI interface for entering Orders into files.
*/

#include "PPP/GUI.h"

using namespace Graph_lib;

//console version is exercise_7_8 (this chapter)
// after typing in a input box hit enter to send line to the program
/* 
output format:

for Order:
{ name, address, data, purchases }

for purchases (vector):
{Purchase,Purchase,Purchase}

for Purchase:
{name,unit_price,count}

example: {name,adress,data,{{name1,12.0,1},{name2,12.3,3},{name3,12.1,13}}}
*/

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
//--------------------------------------

struct My_Out_box : Shape {//handles newline
	My_Out_box(Point p) { Shape::add(p); }

	void put(const string& s)
	{
		istringstream is{ s };
		text_lines.clear();
		for (string i; getline(is, i);)
			text_lines.push_back(i);
		redraw();
	}
	void clear() { text_lines.clear(); redraw();}
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
	Orders_Window(Application&,const string&);
private:
	Application* app;
	//----
	ofstream output_file;
	Order current_order;
	//----
	In_box name_customer_input;//string
	In_box address_customer_input;//string
	In_box data_customer_input;//string
	Button confirm_customer;
	//----
	In_box name_product_input;//string
	In_box price_product_input; //double
	In_box count_product_input;//int
	Button confirm_purchase;
	Button new_order; // new customer
	//----
	My_Out_box text_box;
	Button quit;
	//----
	void confirm_customer_cb();
	void confirm_purchase_cb();
	void new_order_cb();
	//----
};
Orders_Window::Orders_Window(Application& a, const string& file_name)
	:Window{ 1000,600,"Orders Window" }
	, app{ &a }, output_file{file_name,ios::app} // add to the end of file
	
	, name_customer_input{ {0,0},100,20,"Customer name: "}
, address_customer_input{ {0,50},100,20,"Customer address: " }
, data_customer_input{ {0,100},100,20,"Data: " }
, confirm_customer{ {0,160},70,20,"Confirm customer",[this] {confirm_customer_cb(); } }

, name_product_input{ {0,0},100,20,"Product name: " }
, price_product_input{ {0,50},100,20,"Price: " }
, count_product_input{ {0,100},100,20,"Count: " }
, confirm_purchase{ {0,160},70,20,"Confirm purchase",[this] { confirm_purchase_cb(); } }
, new_order{ {200,0},70,20,"Write this Order to the file",[this] { new_order_cb(); text_box.clear(); } }

, text_box{ {0,200} }
, quit{ {x_max() - 70,0},70,20,"Quit",[this] {close(); app->quit(); } }
{
	attach(quit);
	attach(confirm_customer);
	attach(new_order);
	attach(text_box);
	attach(name_customer_input);
	attach(address_customer_input);
	attach(data_customer_input);
	attach(name_product_input);
	attach(price_product_input);
	attach(count_product_input);
	attach(confirm_purchase);
	name_product_input.hide_buttons();
	price_product_input.hide_buttons();
	count_product_input.hide_buttons();
	name_customer_input.hide_buttons();
	address_customer_input.hide_buttons();
	data_customer_input.hide_buttons();

	confirm_purchase.hide();
	new_order.hide();

	name_customer_input.show();
	address_customer_input.show();
	data_customer_input.show();
}
void Orders_Window::new_order_cb()
{
	output_file << current_order << endl; //endl to see changes in the file immediately
	current_order = Order{}; //start with an empty Order

	new_order.hide();
	name_product_input.hide();
	price_product_input.hide();
	count_product_input.hide();
	confirm_purchase.hide();

	name_customer_input.show();
	address_customer_input.show();
	data_customer_input.show();
	confirm_customer.show();
}
void Orders_Window::confirm_purchase_cb()
{
	text_box.clear();
	try
	{
		string product_name = name_product_input.last_string_value();
		if (product_name.empty())
			throw exception{ "product name can't be empty" };

		istringstream iss{ price_product_input.last_string_value() };

		double product_unit_price{0.0};
		if (!(iss >> product_unit_price)) 
			throw exception{ "Product unit price must be a floationg point number" };
		
		iss.clear();
		iss.str( count_product_input.last_string_value());

		int product_count{ 0 };
		if (!(iss >> product_count))
			throw exception{ "Product count must be an ineger number" };

		current_order.purchases.push_back(Purchase{ product_name ,product_unit_price ,product_count });
		text_box.put("new Purchase added");
	}
	catch (exception& errr)
	{
		text_box.put(errr.what());
	}
}
void Orders_Window::confirm_customer_cb()
{
	name_customer_input.hide();
	address_customer_input.hide();
	data_customer_input.hide();
	confirm_customer.hide();

	name_product_input.show();
	price_product_input.show();
	count_product_input.show();
	confirm_purchase.show();
	new_order.show();

	string customer_name =name_customer_input.last_string_value();
	string customer_address = address_customer_input.last_string_value();
	string customer_data = data_customer_input.last_string_value();
	current_order = Order{ customer_name ,customer_address ,customer_data };
}
int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
	Orders_Window win{ app,"data_out.txt"};

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
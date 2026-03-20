/*
[7]
Define an Order class with (customer) name, address, data, and vector<Purchase> members.
Purchase is a class with a (product) name, unit_price, and count members. Define a mecha-
nism for reading and writing Orders to and from a file. Define a mechanism for printing
Orders. Create a file of at least ten Orders, read it into a vector<Order>, sort it by name (of
customer), and write it back out to a file. Create another file of at least ten Orders of which
about a third are the same as in the first file, read it into a list<Order>, sort it by address (of
customer), and write it back out to a file. Merge the two files into a third using std::merge().
[8]
Compute the total value of the orders in the two files from the previous exercise. The value
of an individual Purchase is (of course) its unit_price∗count.
*/

import PPP;
using namespace std;

/* 
input format:

for Order:
{ name, address, data, purchases }

for purchases (vector): 
{Purchase,Purchase,Purchase}

for Purchase:
{name,unit_price,count}

example: {name,adress,data,{{name1,12.0,1},{name2,12.3,3},{name3,12.1,13}}}
*/

string read_string_until(istream& is,const char terminator_ch)
{
	string word;
	char ch{};
	while (is.get(ch) && ch != terminator_ch)
		word += ch;
	if (ch != terminator_ch || !is)
		throw exception{ string("read_until(): expected " + terminator_ch ).c_str()};
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

	v.name=read_string_until(is, ',');

	char ch3{}, ch4{};
	if(!(is >> v.unit_price >> ch3 >> v.count >> ch4) )
		throw exception{ "Bad Purchase reading" };

	if(ch3 != ',')
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
		<<" }";
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

	if (char ch2{}; !(is >> ch2)||ch2 != '}')
		throw exception{ "Bad Purchase termination" };

	return is;
}
//--------------------------------------
double unit_price(const Purchase&p)
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

double orders_price(double init,const Order& o)
{
	cout << "init: " << init << '\n';
	return init + order_price(o);
}
int main()
try {

	ifstream ifs1{ "data1.txt" };
	if (!ifs1) throw exception{ "No file" };

	vector<Order> ord;
	if (!(ifs1 >> ord)) cout << "failed.\n";
	else{
		ranges::sort(ord, [](const Order& o1, const Order& o2) {return o1.name < o2.name; });
		ofstream ofs{ "data_out1.txt" };
		ranges::copy(ord, ostream_iterator<Order>{ofs, "\n"}); // one Order per line
	}

	ifstream ifs2{ "data2.txt" };
	if (!ifs2) throw exception{ "No file" };

	list<Order> l_ord;
	if (!(ifs2 >> l_ord)) cout << "failed.\n";
	else {
		l_ord.sort([](const Order& o1, const Order& o2) {return o1.address < o2.address; });
		ofstream ofs{ "data_out2.txt" };
		ranges::copy(l_ord, ostream_iterator<Order>{ofs, "\n"}); // one Order per line
	}
	l_ord.sort([](const Order& o1, const Order& o2) {return o1.name < o2.name; });
	ofstream ofs{ "data_out_merged.txt" };
	merge(ord.begin(), ord.end(), l_ord.begin(), l_ord.end(), ostream_iterator<Order>{ofs, "\n"},
		[](const Order& o1, const Order& o2) {return o1.name < o2.name; });

	double price{ accumulate(ord.begin(), ord.end(), 0.0, orders_price)
		+ accumulate(l_ord.begin(), l_ord.end(), 0.0, orders_price) };
	cout << "price: "<< price << '\n';
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
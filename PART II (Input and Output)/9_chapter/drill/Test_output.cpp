import PPP;
using namespace std;

class Simple_table {
public:
	string first_name;
	string last_name;
	string telephone_number;
	string email_adress;
};

ostream& operator<<(ostream& os, const Simple_table& st)
{
	constexpr int width{ 20 };
	return os <<left<< setw(width) << "First name: " << st.first_name << '\n'
		<< setw(width) << "Last name: "  << st.last_name << '\n'
		<< setw(width) << "Telephone number: "  << st.telephone_number << '\n'
		<< setw(width) << "Email adress: " << st.email_adress << '\n';
}


class Point {
public:
	int x{ 0 };
	int y{ 0 };
	auto operator<=>(const Point& p)const  = default;
};

ostream& operator<<(ostream& ost, const Point& p)
{
	return ost << '(' << p.x << ',' << p.y << ")";
}

istream& operator>>(istream& is, Point& point)
{
	char d; 
	if (is >> d && d == '(') {
		if (is >> point.x >> d && d == ',') {
			if (is >> point.y >> d && d == ')') {
				return is;
			}
		}
	}
	is.clear(ios::failbit);
	return is;
}
int main()
try {
	ofstream ofs{ "mydata.txt" };
	if (!ofs) throw string{ "Can't open file" };
	
	//Simple_table st{ "Vlad","Gulevsky","175-27-47","superic@yandex.ru" };
//	cout << st << '\n';

	cout << "Enter 7 (x,y) pairs: ";
	vector<Point> original_points;
	int n{ 0 };
	for (Point p; n != 7&& cin >> p; ++n)
		original_points.push_back(p);

	for (Point p : original_points)
			ofs << p << endl;
	ofs.close();

	ifstream ifs{ "mydata.txt" };
	if (!ifs) throw string{ "Can't open file" };

	vector<Point> processed_points;
	for (Point p;  ifs >> p;)
		processed_points.push_back(p);

	if (original_points != processed_points) throw string{ "original_points!= processed_points" };
	
	cout << "Processed points from mydata.txt:\n";
	for (Point p : processed_points)
		cout << p << endl;
	
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
constexpr double d = 1234.56789;
constexpr int n = 1234;
while (true)
{
	cout << format("-{:b}-{:20.8f}-{:30.20e}-\n", n, d, d);
	int n{ 1 };
	cin >> n;
	cout << "n " << n << '\n';
	cout << "cin " << bool(cin) << '\n';
	cout << "e " << cin.eof() << '\n';
	cout << "f " << cin.fail() << '\n';
	cout << "b " << cin.bad() << '\n';
	system("pause");
}
double number = 1234567.89;
int birth_year{ 1994 };
int my_age{ 31 }, a, b, c, d;
cout << defaultfloat << number << '\t' << fixed << number << '\t'
<< scientific << number << '\n';
cin >> a >> oct >> b >> hex >> c >> d;
cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

cout << "birth_year:\n" << showbase;
cout << "dec\t" << dec << birth_year << '\n'
<< "hex\t" << hex << birth_year << '\n'
<< "oct\t" << oct << birth_year << '\n'
<< "binary\t" << bitset<8>(birth_year) << '\n';
cout << "my_age:\n";
cout << "dec\t" << dec << my_age << '\n'
<< "hex\t" << hex << my_age << '\n'
<< "oct\t" << oct << my_age << '\n'
<< "binary\t" << bitset<8>(my_age) << '\n';
chrono::zoned_time zt{ chrono::current_zone(),chrono::system_clock::now() };
cout << "zt: " << zt << '\n';

*/
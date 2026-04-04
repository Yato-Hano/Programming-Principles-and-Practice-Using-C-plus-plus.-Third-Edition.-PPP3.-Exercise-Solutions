/*
[17] 
Write a program that creates a file of data in the form of the temperature Reading type defined
in §9.3.2. For testing, fill the file with at least 50 ‘‘temperature readings.’’ Call this program
store_temps.cpp and the file it creates raw_temps.txt.
[18]
Write a program that reads the data from raw_temps.txt created in exercise 2 into a vector and
then calculates the mean and median temperatures in your data set. Call this program
temp_stats.cpp.
[19] 
Modify the store_temps.cpp program from exercise 2 to include a temperature suffix c for
Celsius or f for Fahrenheit temperatures. Then modify the temp_stats.cpp program to test
each temperature, converting the Celsius readings to Fahrenheit before putting them into the
vector.
[20] 
Write the function print_year() mentioned in §9.9.2.
*/

import PPP;
using namespace std;

class Specification
{
public:
	Specification(vector<double>);
	double min{ 0 };
	double max{ 0 };
	double mean{ 0 };//average
	double median{ 0 };// number in the middle

};
Specification::Specification(vector<double> values) // not passing-by-referenсe because we sort
{
	if (values.size() == 0) throw string{ "No data" };

	double sum = 0;
	for (const double& x : values)
		sum += x;
	mean = sum / values.size();

	sort(values.begin(), values.end());

	max = values[values.size() - 1];
	min = values[0];

	size_t index{ values.size() / 2 };
	if (values.size() % 2)
	{//odd size
		median = values[index]; //exactly in the middle
	}
	else { //even size. 
		median = values[index];
		median += values[index - 1];
		median /= 2.0; //mean of 2 numbers in the middle
	}
}
enum class Suffix {
	Fahrenheit = 'f', Celsius = 'c'
};
struct Reading {
	int day;
	int hour;
	double temperature;//Fahrenheit
	Suffix original_suffix{ Suffix::Fahrenheit};
};

const int not_a_reading = -7777;
const int not_a_month = -1;
struct Day {
	vector<Reading> temp;
};
struct Month {
	// a month of temperature readings
	int month = not_a_month;
	// [0:11] Januar y is 0
	vector<Day> day = vector<Day>(32);
	// [1:31] one vector of readings per day
};
struct Year {
	// a year of temperature readings, organized by month
	int year;
	// positive == A.D.
	vector<Month> month = vector<Month>(12);
	// [0:11] Januar y is 0
};
bool operator<(const Reading& r1, const Reading& r2)
{
	return r1.temperature < r2.temperature;
}

double get_fahrenheit(double value, char simbol)
{
	switch (Suffix(simbol))
	{
		case Suffix::Celsius:
			return (value * 1.8) + 32;
		case Suffix::Fahrenheit:
			return value;
		default:
		PPP::error("bad reading, not a Suffix ", simbol);
	}
}
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;
bool is_valid(const Reading& r)
// a rough test
{
	if (r.day < 1 || 31 < r.day)
		return false;
	if (r.hour < 0 || 23 < r.hour)
		return false;
	if (r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}

void end_of_loop(istream & ist, char term, const string & message)
{	if (ist.fail()) {
			// use term as ter minator and/or separator
			ist.clear();
			char ch = 0;
			if (ist >> ch && ch == term)
				return;
			// all is fine
			PPP::error(message);
		}
}
vector<string> month_input_tbl = {
"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
};
int month_to_int(string s)
// is s the name of a month? If so return its index [1:12] otherwise -1
{
	for (int i = 0; i < month_input_tbl.size(); ++i)
		if (month_input_tbl[i] == s)
			return i;
		return -1; 
}

istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r. for mat: ( 3 4 9.7 )
// check for mat, but don’t bother with data validity
{
	if (is.eof())return is;
	char ch1{};
	if (is >> ch1 && ch1 != '(') {
		// could it be a Reading?
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	char ch2{}, ch3{};
	if ((is >> r.day >> r.hour >> r.temperature >> ch2 >> ch3) && ch3 != ')')
		PPP::error("bad reading>>");

	if (is)
	{
		r.temperature = get_fahrenheit(r.temperature, ch2);
		r.original_suffix = Suffix(ch2);
	}
	return is;
}
istream& operator>>(istream& is, Month& m)
// read a month from is into m. for mat: { month feb . . . }
{
	char ch = 0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(ios::failbit);
		// we failed to read a Month
		return is;
	}
	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month")
		PPP::error("bad start of month");
	m.month = month_to_int(mm);
	if(m.month==-1)
		PPP::error("bad month");
	//cout << "m.month " << m.month<<'\n';
	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r; ) {
		if (is_valid(r))
		{
			//if (m.day[r.day].temp[r.hour].temperature != not_a_reading)	++duplicates;
			m.day[r.day].temp.push_back(r);
		}
		else
			++invalids;
	}
	if (invalids)
		PPP::error("invalid readings in month", invalids);
	if (duplicates)
		PPP::error("duplicate readings in month", duplicates);
	end_of_loop(is, '}', "bad end of month");
	return is;
}
istream& operator>>(istream& is, Year& y)
// read a year from is into y. for mat: { year 1972 ... }
{
	char ch = 0;
	is >> ch;
	if (ch != '{') {
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	string year_marker;
	int yy = -1;
	is >> year_marker >> yy;
	if (!is || year_marker != "year")
		PPP::error("bad start of year");
	y.year = yy;
	while (true) {
		Month m;
		// get a clean m each time around
		if (!(is >> m))
			break;
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}
ostream& operator<<(ostream& os, const Reading& r)
{
	return os << '(' << r.day << ' ' << r.hour << ' ' << r.temperature << ' ' << char(r.original_suffix) << ')';
}
void print_day(ostream& os, const Day& d)
{
	for (Reading r : d.temp) os <<' ' << r;
}
void print_month(ostream& os, const Month& d)
{
	if (d.month == not_a_month) return;
	os << " { month " << month_input_tbl[d.month]<<' ';
	for (Day r : d.day) { print_day(os, r); }
	os << " } ";
}
void print_year(ostream& os, const Year& y)
{
	os << " { year " << y.year << ' ';
	for (Month r : y.month) { print_month(os, r); }
	os << " }\n";
}
inline int rand_int(int min, int max)
{
	static default_random_engine ran{ unsigned(time(0)) };
	return uniform_int_distribution<>{min, max}(ran);
}

void create_rand_readings(string file_name)
{
	ofstream ofs{ file_name };
	if (!ofs) throw exception{ "No file" };
	for (size_t i = 0; i < 50; i++)
		ofs << Reading{ rand_int(0,31),rand_int(0,24),double(rand_int(0,100)),Suffix::Celsius } << '\n';
}

vector<Reading> get_readings(string file_name)
{
	ifstream ifs{ file_name };
	if (!ifs) throw exception{ "No file" };
	vector<Reading> data;
	while (ifs)
	{
		Reading i;
		if(ifs >> i)
			data.push_back(i);
	}
	if (!ifs.eof())  throw exception{ "Bad reading, Not eof()" };
	return data;
}
vector<double> get_temperatures(vector<Reading> r)
{
	vector<double> temp;
	for (const Reading& x : r)
	{
		temp.push_back(x.temperature);
	}
	return temp;
}

int main()
try {
	string file_name{ "raw_temps.txt" };

	create_rand_readings(file_name);

	vector<Reading> data =get_readings(file_name);
	vector<double> data_temps = get_temperatures(data);

	Specification s{ data_temps };
	cout << "Min: " << s.min << '\n'
		<< "Max: " << s.max << '\n'
		<< "Mean: " << s.mean << '\n'
		<< "Median: " << s.median << '\n';

	ifstream ifs{ "y.txt" };
	if (!ifs) throw exception{ "No file" };
	

	vector<Year> ys;
	while (true) {
		Year y;
		// get a freshly initialized Year each time around
		if (!(ifs >> y))
			break;
		ys.push_back(y);
	}
	cout << "read " << ys.size() << " years of readings\n";
	ofstream ofs{ "out_y.txt" };
	if (!ofs) throw exception{ "No file" };
	for (Year& y : ys)
		print_year(ofs, y);

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
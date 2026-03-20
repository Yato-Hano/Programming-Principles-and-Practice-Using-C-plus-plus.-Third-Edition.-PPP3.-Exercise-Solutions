/*
[4]
Read a file of integers into a vector. Measure how long the reading took. Use chrono
(§20.4). Sort the vector, and measure how long the sorting took. You will need a large file to
get any useful data. Generate the file of at least a million integers using random (§20.4).
[5]
Read the file of integers from the previous exercise into a set. Measure how long the reading
and creation of the set took.
[6]
Do the previous exercise with an unsorted_set. Did the timings from this and the previous
two exercises match your expectations?
[7]
Repeat the previous three exercises with a file of random character strings. Each string
should contain only letters and digits. Each string should have between 4 and 24 characters.
*/

import PPP;
using namespace std;
using namespace chrono;

inline int rand_int(int min, int max)
{
	static default_random_engine ran{ unsigned(time(0)) };
	return uniform_int_distribution<>{min, max}(ran);
}
//--------------------------------------------
vector<int> generate_ints(size_t size_number)
{
	static vector<int> numbers;
	if(numbers.empty())
	{
		numbers.reserve(size_number);
		for (size_t i = 0; i < size_number; i++)
			numbers.push_back(rand_int(-100, 100));
	}
	return numbers;
}

string create_word()
{
	static const string valid_chars =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";
	static const int max_ch( valid_chars.size() - 1 );

	int length{ rand_int(4, 24) };
	string word;
	word.reserve(length);

	for (length; length!=0;length--)	{
		word += char(valid_chars[rand_int(0, max_ch)]);
	}
	return word;
}
vector<string> generate_strings(size_t size_number)
{
	static vector<string> words;
	if (words.empty())
	{
		words.reserve(size_number);
		for (size_t i = 0; i < size_number; i++)
			words.push_back(create_word());
	}
	return words;
}

void create_file_strings(size_t size_number)
{
	ofstream ofs{ "data_str.txt" };
	ranges::copy(generate_strings(size_number), ostream_iterator<string>(ofs, "\n"));
}

void create_file_ints(size_t size_number)
{
	ofstream ofs{ "data.txt" };
	ranges::copy(generate_ints(size_number), ostream_iterator<int>(ofs, "\n"));
}

void create_file_ints_endl(size_t size_number)
{
	ofstream ofs{ "data.txt" };
	vector<int> n{ generate_ints(size_number) };
	for (const int& nn : n)ofs << nn << endl;
}

void create_file_ints_(size_t size_number)
{
	ofstream ofs{ "data.txt" };
	vector<int> n{ generate_ints(size_number) };
	for (const int& nn : n)ofs << nn << '\n';
}
template <typename T>
void measure_vector_and_print(size_t size_number)
{
	ifstream ifs;
	if constexpr (std::is_same_v<T, int>)
	{
		ifs.open("data.txt");
		cout << "vector<int>(" << size_number << ")\n";

	}
	else
		if constexpr (std::is_same_v<T, string>)
	{
		ifs.open("data_str.txt");
		cout << "vector<string>(" << size_number << ")\n";
	}

	if (!ifs) throw exception{ "No file" };

	vector<T> numbers;
	numbers.reserve(size_number);
	auto t0 = system_clock::now();
	for (T n{}; ifs >> n;) numbers.push_back(n);
	auto t1 = system_clock::now();
	cout << "reading took:\t"  <<duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";
	t0 = system_clock::now();
	ranges::sort(numbers);
	t1 = system_clock::now();
	cout << "sorting took:\t" << duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";

}
//--------------------------------------------

template <typename T>
void measure_set_and_print(size_t size_number)
{
	ifstream ifs;
	if constexpr (std::is_same_v<T, int>)
	{
		ifs.open("data.txt");
		cout << "set<int>(" << size_number << ")\n";

	}
	else
		if constexpr (std::is_same_v<T, string>)
		{
			ifs.open("data_str.txt");
			cout << "set<string>(" << size_number << ")\n";
		}

	if (!ifs) throw exception{ "No file" };

	set<T> st;
	auto t0 = system_clock::now();
	for (T n{}; ifs >> n;) st.insert(n);
	auto t1 = system_clock::now();
	cout << "reading took:\t" << duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";
}

template <typename T>
void measure_unordered_set_and_print(size_t size_number)
{
	ifstream ifs;
	if constexpr (std::is_same_v<T, int>)
	{
		ifs.open("data.txt");
		cout << "unordered_set<int>(" << size_number << ")\n";

	}
	else
		if constexpr (std::is_same_v<T, string>)
		{
			ifs.open("data_str.txt");
			cout << "unordered_set<string>(" << size_number << ")\n";
		}
	if (!ifs) throw exception{ "No file" };

	unordered_set<T> st;
	auto t0 = system_clock::now();
	for (T n{}; ifs >> n;) st.insert(n);
	auto t1 = system_clock::now();
	cout << "reading took:\t" << duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";
}
int main()
try {
	size_t size_number{ 1000000 };
	/*auto t0 = system_clock::now();
	create_file_strings(size_number);
	auto t1 = system_clock::now();
	cout << "creation took:\t" << duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";

	
	auto t0 = system_clock::now();
	create_file_ints_(size_number);
	auto t1 = system_clock::now();
	cout << "creation took:\t" << duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";
	
	t0 = system_clock::now();
	create_file_ints(size_number);
	t1 = system_clock::now();
	cout << "creation took:\t" << duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";
	
	t0 = system_clock::now();
	create_file_ints_endl(size_number);//very slow (2.5x time)
	t1 = system_clock::now();
	cout << "creation took:\t" << duration_cast<microseconds>(t1 - t0).count() << " microseconds\n";
	*/
	measure_vector_and_print<int>(size_number); 
	measure_vector_and_print<string>(size_number); //the same as vector<int> but sorting 2x times slower

	measure_set_and_print<int>(size_number);
	measure_set_and_print<string>(size_number); // 2.5x time longer than set<int> because of string comparison

	measure_unordered_set_and_print<int>(size_number);
	measure_unordered_set_and_print<string>(size_number); // 1.5x times slower than unordered_set<int>

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
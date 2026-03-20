/*
[15]
Look up (e.g., on the Web) skip list and implement that kind of list. This is not an easy exer-
cise.
*/

import PPP;
using namespace std;

inline int rand_int(int min, int max)
{
	static default_random_engine ran{ unsigned(time(0)) };
	return uniform_int_distribution<>{min, max}(ran);
}

class Skip_list {
public:
	void insert(int val);
	bool find(int val)const;
	void erase(int val);
	const auto& get_data()const { return levels; }
	int size()const { return current_sz; }
private:
	vector<set<int>> levels= vector<set<int>>(8);
	int current_sz{ 0 };
};
bool  Skip_list::find(int val)const
{
	for (int i = current_sz -1; 0<=i; i--)
	{
		if(levels[i].find(val)!= levels[i].end())
			return true;
	}
	return false;
}
void Skip_list::insert(int val)
{
	if (0==current_sz)current_sz=1;
	levels[0].insert(val);
	for (int i{ 1 }; current_sz< levels.size()&& rand_int(0, 1); ++i)
	{
		if (i == current_sz)++current_sz;
		levels[i].insert(val);
	}
}
void Skip_list::erase(int val)
{
	int decrement{ 0 };
	for (int i{ 0 }; i < current_sz && levels[i].erase(val); ++i)
		if(levels[i].empty())decrement++;
	current_sz -= decrement;
}

void print_set(const set<int>&d)
{
	for (const int& n : d)cout << n << ' ';
}
void print_skip_list(const Skip_list& sl)
{
	for (size_t i = 0; i < sl.size(); i++)
	{
		cout << 'L' << i << ": ";
		print_set(sl.get_data()[i]);
		cout << '\n';
	}
}

int main()
try {
	Skip_list sl;

	for (size_t i = 0; i < 100; i++)
	{
		sl.insert(i);
	}
	print_skip_list(sl);
	cout << "erase()";
	for (int i = 0; cin >> i && 0 <= i;)
	{
		sl.erase(i);
		cout << "erasing val "<<i<<'\n';
		print_skip_list(sl);
	}
	cout << "insert()";
	for (int i = 0; cin >> i && 0 <= i;)
	{
		sl.insert(i);
		cout << "inserting val " << i << '\n';
		print_skip_list(sl);
	}
	cout << "find()";
	for (int i = 0; cin>>i&&0<=i;)
	{
		cout << "found " << sl.find(i) << "\n";
	}
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
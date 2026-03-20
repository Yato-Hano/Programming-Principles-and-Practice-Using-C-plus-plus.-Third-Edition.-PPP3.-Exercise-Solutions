/*
[17] 
Define a function finally() that takes a function object as its arguments and returns an
object with a destructor that invokes that function object. Thus
	auto x = finally([](){ cout<< "Bye!\n"; });
will ‘‘say’’ Buy! whenever we exit the scope of x. For what might finally() be useful?
*/

import PPP;
using namespace std;

template<typename F>
class Final_act {
	F f;
public:
	explicit Final_act(F func) :f{func}{}
	~Final_act() { f(); }
};

template<typename F>
Final_act<F> finnaly(F f)
{
	return Final_act<F>{f};
}
void test()
{
	finnaly([] {cout << "bye\n"; });
}
int main()
try {
	test();
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
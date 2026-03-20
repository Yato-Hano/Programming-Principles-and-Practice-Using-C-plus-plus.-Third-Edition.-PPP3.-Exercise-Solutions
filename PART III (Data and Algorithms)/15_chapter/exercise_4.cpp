/*
[4]
Consider the memory layout in §15.4. Write a program that tells the order in which static
storage, the stack, and the free store are laid out in memory. In which direction does the
stack grow: upward toward higher addresses or downward toward lower addresses? In an
array on the free store, are elements with higher indices allocated at higher or lower
addresses?
*/

import PPP;
using namespace std;

int stat{0};

int main()
try {
	int stack {1};
	int* fr = new int{2};


	vector<int*>v{ &stat,&stack ,fr };

	sort(v.begin(), v.end());

	for (size_t i = 0; i < 3; i++)
	{
		cout<<*v[i] <<' ';
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
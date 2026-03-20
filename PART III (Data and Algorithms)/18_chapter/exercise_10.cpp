/*
[10] 
Implement a simple unique_ptr supporting only a constructor, destructor, −>, ∗, and
release(). Delete the assignment and copy constructors.
*/

import PPP;
using namespace std;

template<typename T>
class Unique_ptr
{
	T* ptr;
public:
	explicit Unique_ptr(T* p) :ptr{ p } {}
	T& operator*() { return *ptr; }
	T* operator->() { return ptr; }

	~Unique_ptr() { delete ptr;	}

	T* release()
	{
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	Unique_ptr(const Unique_ptr&) = delete;
	Unique_ptr& operator=(const Unique_ptr&) = delete;
};
int main()
try {
	Unique_ptr<int>p(new int(42));
	Unique_ptr<int>p2 ( p.release());
	//cout << *p << '\n';
	cout << *p2 << '\n';
	Unique_ptr<vector<int>>pv(new vector<int>());
	cout << pv->size() << '\n';
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
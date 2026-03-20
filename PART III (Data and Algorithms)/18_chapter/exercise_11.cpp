/*
[11] 
Design and implement a Counted_ptr<T> that is a type that holds a pointer to an object of
type T and a pointer to a ‘‘use count’’ (an int) shared by all counted pointers to the same
object of type T. The use count should hold the number of counted pointers pointing to a
given T. Let the Counted_ptr’s constructor allocate a T object and a use count on the free
store. Let Counted_ptr’s constructor take an argument to be used as the initial value of the
T elements. When the last Counted_ptr for a T is destroyed, Counted_ptr’s destructor
should delete the T. Giv e the Counted_ptr operations that allow us to use it as a pointer.
This is an example of a ‘‘smart pointer’’ used to ensure that an object doesn’t get
destroyed until after its last user has stopped using it. Write a set of test cases for
Counted_ptr using it as an argument in calls, container elements, etc.
*/

import PPP;
using namespace std;

template<typename T>
class Counted_ptr
{
	T* ptr;
	int* count;
public:
	explicit Counted_ptr(T* p);
	Counted_ptr(const Counted_ptr& other);
	Counted_ptr& operator=(const Counted_ptr& other);
	T& operator*() { return *ptr; }
	T* operator->() { return ptr; }
	int count_number()const { return *count; }
	~Counted_ptr() { release();  }
private:
	void release();
};

template<typename T>
void Counted_ptr<T>::release()
{
	if (count == nullptr)return;

	--(*count);

	if (*count == 0)
	{
		delete count;
		delete ptr;
		return;
	}
	count = nullptr;
	ptr = nullptr;
}

template<typename T>
Counted_ptr<T>::Counted_ptr(T* p)
	:ptr{ p }, count{ nullptr }
{
	if (ptr)
		count = new int{ 1 };
}
template<typename T>
Counted_ptr<T>::Counted_ptr(const Counted_ptr& other)
	:ptr{ other.ptr }, count{ other.count }
{
	if (count)
		++(*count);
}
template<typename T>
Counted_ptr<T>& Counted_ptr<T>::operator=(const Counted_ptr<T>& other)
{
	if (&other == this)
		return *this;

	release();
	ptr = other.ptr;
	count = other.count;

	if (count)
		++(*count);

	return *this;
}

int main()
try {
	Counted_ptr<int> a{ new int(10) };
	Counted_ptr<int> b{ a };
	cout << b.count_number() << '\n';
	a.~Counted_ptr();
	cout << b.count_number() << '\n';
	b.~Counted_ptr();
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
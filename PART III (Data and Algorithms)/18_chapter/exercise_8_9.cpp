/*
[8]
Implement an allocator (§18.2) using the most basic standard-library allocation functions
malloc() and free(). Get Vector as defined by the end of §18.3 to work for a few simple test
cases.
[9]
Re-implement Vector::operator=() (§17.8.5) using an allocator (§18.2) for memory man-
agement
*/

import PPP;
using namespace std;

template<typename T>
class Alocator
{
public:
	T* allocate(int n)
	{
		if (n < 0) return nullptr;
		return static_cast<T*>(malloc(n*sizeof(T)));
	}
	void deallocate(T* p, int n=0)
	{
		free(p);
	}
};
template<typename T, typename A = allocator<T>>
// for all types T (just like in math)
class Vector {
	int sz;
	A alloc;
	T* elem;
	int space;
public:
	Vector() :sz{ 0 }, elem{ nullptr }, space{ 0 } {}
	
	explicit Vector(int s) :sz{ s }, elem{ alloc.allocate(s) }, space{s}
	{
		for (int i = 0; i < sz; ++i)
			elem[i] = T{};
	}

	Vector(initializer_list<T>);
	Vector(const Vector&);
	Vector(Vector&&);

	Vector& operator=(initializer_list<T>);
	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);

	~Vector() {
		destroy_n(elem, space);
		alloc.deallocate(elem, space);
	}

	T& at(int n);
	const T& at(int n) const;
	T& operator[](int n) { return elem[n]; }
	const T& operator[](int n) const { return elem[n]; }

	int size() const { return sz; }
	int capacity() const { return space; }

	void resize(int newsize);
	void push_back(const T& d);
	void reserve(int newalloc);

	T* begin() const { return elem; }
	T* end() const { return elem + sz; }

	auto operator<=>(const Vector&)const = default;
};
template<typename T, typename A>
Vector<T, A>& Vector<T, A>::operator=(const Vector<T, A>& a)
{
	if (this == &a)
		return *this;

	if (a.sz <= space) 
	{
		for (int i = 0; i < a.sz; ++i)
			elem[i] = a.elem[i];
		sz = a.sz;
		return *this;
	}
	T* p = alloc.allocate(a.sz);
	for (int i = 0; i < a.sz; ++i)
		p[i] = a.elem[i];

	destroy_n(elem, space);
	alloc.deallocate(elem, space);

	space = sz = a.sz;
	elem = p;
	return *this;
}
template<typename T, typename A>
void Vector<T, A>::reserve(int newalloc) 
{
	if (newalloc <= space)
		return;

	T* p = alloc.allocate(newalloc);
	uninitialized_move(elem, &elem[sz], p);
	destroy_n(elem, space);
	alloc.deallocate(elem, space);
	elem = p;
	space = newalloc;
}
template<typename T, typename A>
T& Vector<T, A>::at(int n)
{
	if (n < 0 || sz <= n)
		throw out_of_range("out of range");
	return elem[n];
}
void test()
{
	Vector<int, Alocator<int>>v(4);
	v.reserve(5);
	Vector<int, Alocator<int>>v2;
	v2 = v;
	cout << v2.at(3) << '\n';
	cout << "v size " << v.size() << ' ' << "v capacity " << v.capacity() << '\n';
	cout << "v2 size " << v2.size() << ' ' << "v2 capacity " << v2.capacity() << '\n';
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
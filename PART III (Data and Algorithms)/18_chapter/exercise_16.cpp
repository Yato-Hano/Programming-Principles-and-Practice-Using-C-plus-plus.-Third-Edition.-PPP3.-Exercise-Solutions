/*
[16] 
Sometimes, it is desirable that an empty vector be as small as possible. For example,
someone might use vector<vector<vector<int>>> a lot but have most element vectors
empty. Define a Vector so that siz eof(Vector<int>)==siz eof(int∗), that is, so that the Vector
itself consists only of a pointer to a representation consisting of the elements, the number
of elements, and the space pointer.
*/

import PPP;
using namespace std;

template<typename T>
struct Rep
{
	T* elem;
	int sz, space;
};

template<typename T>
class Vector 
{
	Rep<T>* rep;
public:
	Vector() :rep{ nullptr }{}
	explicit Vector(int sz)
		:rep{new T[sz],sz,sz}{ }

	~Vector() {
		if (rep){
			delete[]rep->elem;
			delete rep;
		}
	}
	int size()const { return rep ? rep->sz : 0; }
	T& operator[](int i)
	{
		return rep->elem[i];
	}
	const T& operator[](int i)const
	{
		return rep->elem[i];
	}
	Vector(const Vector&) = delete;
	Vector& operator=(const Vector&) = delete;
};
int main()
try {
	cout << sizeof(Vector<int>) << '\n';
	cout << sizeof(vector<int>) << '\n';
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
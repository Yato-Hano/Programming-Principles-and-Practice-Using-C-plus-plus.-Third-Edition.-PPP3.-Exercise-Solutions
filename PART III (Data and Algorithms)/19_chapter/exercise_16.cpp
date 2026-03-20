/*
[16] 
Define an Ovector that is like Pvector except that the [ ] and ∗ operators return a reference to
the object pointed to by an element rather than the pointer.
*/

import PPP;
using namespace std;

template<class T>
class Ovector {
    vector<T*> elems;
public:
    class iterator;
    Ovector() {}
    Ovector(Ovector&& pv)
        :elems{ std::move(pv.elems) }
    {
        pv.elems.clear();
    }
    Ovector(Ovector&) = delete;
    Ovector& operator=(const Ovector&) = delete;

    void push_back(T* p) { elems.push_back(p); }

    ~Ovector() { clear(); }
    void clear()
    {
        for (T* p : elems)
            delete p;
        elems.clear();
    }
    T& operator[](int i) { return *elems[i]; }
    const T& operator[](int i) const { return *elems[i]; }

    int size() const { return elems.size(); }
    iterator begin() { return iterator{ elems.begin() }; }
    iterator end() { return iterator{ elems.end() }; }
};


template<class T>
class Ovector<T>::iterator
{
    vector<T*>::iterator it;
public:
    explicit iterator(vector<T*>::iterator i) :it{ i } {}
    T& operator*() { return **it; }
    T* operator->() { return *it; }
    iterator& operator++() { ++it; return *this; }
    bool operator==(const iterator& b) const { return it == b.it; }
    bool operator!= (const iterator& b) const { return it != b.it; }
};

int main()
try {
    Ovector<int>ov;
    ov.push_back(new int{ 4 });
    ov.push_back(new int{ 2 });

    for (int n : ov)
        cout << n << ' ';
    cout << '\n';

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
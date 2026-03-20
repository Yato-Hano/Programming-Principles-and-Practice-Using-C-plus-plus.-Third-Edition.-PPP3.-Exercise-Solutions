/*
[17]
Define an Ownership_vector that holds pointers to objects like Pvector but provides a mecha-
nism for the user to decide which objects are owned by the vector (i.e., which objects are
deleted by the destructor). Hint: This exercise is simple if you were awake for Chapter 11.
*/

import PPP;
using namespace std;


template<class T> class Ownership_vector {
    vector<T*> v;
    vector<T*> owned;
public:
    Ownership_vector() {}

    ~Ownership_vector()
    {
        clear();
    }
    void clear()
    {
        for (T* p : owned)
            delete p;
        v.clear();
        owned.clear();
    }
    void push_back(T& s) { v.push_back(&s); }
    void push_back(T* p) { v.push_back(p); owned.push_back(p); }

    T& operator[](int i) { return *v[i]; }
    const T& operator[](int i) const { return *v[i]; }
    int size() const { return v.size(); }
    vector<T*>::iterator begin() { return v.begin(); }
    vector<T*>::iterator end() { return v.end(); }
};


int main()
try {
    int a{ 1 };
    Ownership_vector<int> ov;

    ov.push_back(a);
    ov.push_back(new int{ 3 });
    for (int* n : ov)
        cout << *n << ' ';
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
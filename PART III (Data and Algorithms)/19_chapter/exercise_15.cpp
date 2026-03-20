/*
[15] 
Define a Pvector to be like a vector of pointers except that it contains pointers to objects and
its destructor deletes each object.
*/

import PPP;
using namespace std;

template<class T> 
class Pvector {
    vector<T*> elems;
public:
    Pvector() {}
    Pvector(Pvector&& pv)
        :elems{std::move(pv.elems)}
    {
        pv.elems.clear();
    }
    Pvector(Pvector&) = delete;
    Pvector& operator=(const Pvector&) = delete;

    void push_back(T* p)    {        elems.push_back(p);    }

    ~Pvector() {  clear(); }
    void clear()
    {
        for (T* p : elems)
            delete p;
        elems.clear();
    }
    T& operator[](int i) { return *elems[i]; }
    const T& operator[](int i) const { return *elems[i]; }

    int size() const { return elems.size(); }

    auto begin() { return elems.begin(); }
    auto end() { return elems.end(); }
    auto begin() const { return elems.begin(); }
    auto end() const { return elems.end(); }
};

int main()
try {
    Pvector<int> pv;
    pv.push_back(new int{ 3 });
    Pvector<int> pv2{ move(pv )};
    cout << pv2[0] << '\n';
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
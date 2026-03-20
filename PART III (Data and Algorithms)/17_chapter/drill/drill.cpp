/*

*/

import PPP;
using namespace std;

class Ptr
{
public:
	Ptr();
	explicit Ptr(double);
	Ptr(const Ptr&);
	Ptr( Ptr&&);
	Ptr& operator=(const Ptr&);
	Ptr& operator=( Ptr&&);
	double& operator*() { return *p; }
	const double& operator*() const{ return *p; }
	~Ptr();
private:
	double* p;
};
Ptr::Ptr(Ptr&& n)
{
	cout << "Ptr(Ptr&& n)\n";
	p = n.p;
	n.p = nullptr;
}
Ptr& Ptr::operator=(Ptr&&n)
{
	cout << "operator=(Ptr&&n)\n";
	if (this == &n)return *this;
	if (p) delete p;
	p = n.p;
	n.p = nullptr;
	return *this;
}

Ptr& Ptr::operator=(const Ptr& n)
{
	cout << "operator=(Ptr&n)\n";
	if (this == &n)return *this;
	if (p) delete p;
	if (!n.p) p = nullptr;
	else p=	new double{ *n.p };
	return *this;
}
Ptr::Ptr(const Ptr&n)
	:p{ new double{*n.p} }
{
	cout << "Ptr(const Ptr&n)\n";
}
Ptr::Ptr()
	:p{nullptr}
{
	cout << "Ptr()\n";

}
Ptr::~Ptr()
{
	cout << "~Ptr()\n";
	if(p)
		delete p;
}
Ptr::Ptr(double d)
	:p{ new double{d} }
{
	cout << "Ptr(double d)\n";
}

Ptr f()
{
	Ptr p4{ 5 };
	return p4;

}
int main()
try {
	Ptr p{ 1 }; 
	Ptr p2{ 3 };
	Ptr p3{ p2 };
	p = p3; // copy  assignment
	


	cout << *p << '\n';//3
	cout << *p2 << '\n';//3
	cout << *p3<<'\n';//3

	{
		Ptr p4{ 4 };
		p3 = p4; //move

	}
	cout << *p3 << '\n';//4
	p3 = f(); //move
	cout << *p3 << '\n';//5
	Ptr p4 = f(); 
	cout << *p4<< '\n';

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
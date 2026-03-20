/*
[12] 
Complete the definition of list from §19.3 and get the high() example to run. Allocate a Link
to represent one past the end.
*/

import PPP;
using namespace std;

template<typename T>
struct Link {
	Link* prev;
	Link* succ;
	T val;
};
template<typename T>
class List 
{
	Link<T>*first;
	Link<T>*last;
public:
	List();
	List(size_t, const T & = T{});
	List( List<T>&);
	List(const initializer_list<T>&);
	List(List<T>&&);
	List<T>& operator=(const List<T>&) = delete;
	~List();

	class iterator;

	iterator begin() { return iterator{ first }; }
	iterator end() { return iterator{ nullptr }; }

	iterator insert(iterator p, const T& v);
	iterator erase(iterator p);

	void push_back(const T& v) { insert(end(), v); }
	void push_front(const T& v) { insert(begin(), v); }

	void pop_front(){erase(iterator{ first });}
	void pop_back(){erase(iterator{ last });}

	T& front()	{	return first->val;	}
	T& back() { return last->val; }
};
template<typename T>
class List<T>::iterator
{
	Link<T>* curr;
public:
	Link<T>* get_curr()const { return curr; }
	iterator(Link<T>* p) :curr{ p } {}
	iterator& operator++() { curr = curr->succ; return *this; }
	iterator& operator--() { curr = curr->prev; return *this; }
	T& operator*() { return curr->val; }
	bool operator==(const List<T>::iterator& b) const { return curr == b.curr; }
	bool operator!= (const List<T>::iterator& b) const { return curr != b.curr; }
};
template<typename T>
List<T>::iterator List<T>::insert(iterator p, const T& v)
{
	if (!first) // empty list
	{
		first = last = new Link<T>{nullptr,nullptr,v};
		return iterator{ first };
	}
	if (p.get_curr() == nullptr) //insert()at end()
	{
		Link <T>*new_link= new Link<T>{ last,nullptr,v };
		last->succ = new_link;
		last= new_link;
		return iterator{ new_link };
	}
	Link<T>* curr = p.get_curr();
	Link<T>* prev = curr->prev;

	Link <T>*new_link = new Link<T>{ prev,curr,v };
	curr->prev = new_link;

	if (prev)
		prev->succ = new_link;
	else
		first = new_link;
	return iterator{ new_link };
}
template<typename T>
List<T>::iterator List<T>::erase(iterator p)
{
	if (p.get_curr() == nullptr)return p;

	Link<T>* curr = p.get_curr();
	Link<T>* next = curr->succ;
	Link<T>* prev = curr->prev;

	if (prev)
		prev->succ = next;
	else
		first = next;

	if (next)
		next->prev = prev;
	else
		last = prev;

	delete curr;
	return iterator{ next };
}
template<typename T>
List<T>::List( List<T>&l)
{
	for ( T& t : l)push_back(t);
}
template<typename T>
List<T>::List(size_t number_of_elements,const T& t)
{
	while(number_of_elements)
	{
		push_back(t);
		--number_of_elements;
	}
}
template<typename T>
List<T>::List(const initializer_list<T>&il)
{
	for (const T& t : il)push_back(t);
}
template<typename T>
List<T>::List() 
	:first{ nullptr }, last{ nullptr } 
{}
template<typename T>
List<T>::List(List<T>&&ll)
	: first{ ll.first }, last{ ll.last }
{
	ll.first = nullptr;
	ll.last = nullptr;
}
template<typename T>
List<T>::~List()
{
	Link<T>* current = first;     
	while (current != nullptr) 
	{
		Link<T>* next= current->succ;
		delete current;
		current = next;             
	}
	first = last = nullptr;
}

template<typename T>
void print( List<T>& l)
{
	cout << "{ ";
	for ( auto& v : l)cout << v << ' ';
	cout << "}\n";
}
int main()
try {
	List<int> l{ 1,2,3 };
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
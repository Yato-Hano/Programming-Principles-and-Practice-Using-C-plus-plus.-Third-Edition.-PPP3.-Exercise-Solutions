/*
[14]
Define a singly-linked list, Slist, in the style of std::list. Which operations from list could you
reasonably eliminate from Slist because it doesn’t hav e back pointers?
*/

import PPP;
using namespace std;

template<typename T>
struct Link {
	Link* succ;
	T val;
};
template<typename T>
Link<T>* get_to_the_last(Link<T>* l)
{
	if (!l)return nullptr;
	while (l->succ)
		l = l->succ;
	return l;
}

template<typename T>
class SList
{
	Link<T>* first;
public:
	SList();
	SList(SList<T>&) = delete;
	SList(SList<T>&&);
	SList<T>& operator=(const SList<T>&) = delete;
	~SList();

	class iterator;

	iterator begin() { return iterator{ first }; }
	iterator end() { return iterator{ nullptr }; }

	iterator erase(iterator p);//not efficient  for this type of list
	iterator insert(iterator p, const T& v);//not efficient  for this type of list
	iterator insert_after(iterator p, const T& v);
	iterator erase_after(iterator p);

	void push_front(const T& v) { first = new Link<T>{ first ,v}; }

	void pop_front() {
		Link<T>* new_first = first->succ;
		delete first;
		first = new_first;
	}

	T& front() { return first->val; }
	T& back() { return get_to_the_last(first)->val; }
};
template<typename T>
class SList<T>::iterator
{
	Link<T>* curr;
public:
	Link<T>* get_curr()const { return curr; }
	iterator(Link<T>* p) :curr{ p } {}
	iterator& operator++() { curr = curr->succ; return *this; }
	T& operator*() { return curr->val; }
	bool operator==(const SList<T>::iterator& b) const { return curr == b.curr; }
	bool operator!= (const SList<T>::iterator& b) const { return curr != b.curr; }
};
template<typename T>
SList<T>::iterator SList<T>::erase(iterator p)
{
	Link<T>* curr = p.get_curr();

	if (curr == nullptr)
		return end();

	if (curr == first)
		pop_front();

	Link<T>* prev = first;
	while (prev && prev->succ != curr)
		prev = prev->succ;

	if (prev == nullptr)
		return end();
	prev->succ = curr->succ;
	delete curr;
	return iterator{ prev->succ };
}

template<typename T>
SList<T>::iterator SList<T>::insert(iterator p, const T& v)
{
	Link<T>* curr = p.get_curr();
	if (curr == first)	{
		push_front(v);
		return iterator{ first };
	}

	Link<T>* prev = first;
	while (prev && prev->succ != curr)
		prev = prev->succ;

	if (prev == nullptr) return end();

	Link<T>* new_link = new Link<T>{ curr ,v };
	prev->succ = new_link;
	return iterator{ new_link };
}
template<typename T>
SList<T>::iterator SList<T>::insert_after(iterator p, const T& v)
{
	Link<T>* curr = p.get_curr();
	if (curr == nullptr)
		return p;

	Link<T>*new_link= new Link<T>{ curr->succ ,v };
	curr->succ = new_link;
	return iterator{ new_link };
}
template<typename T>
SList<T>::iterator SList<T>::erase_after(iterator p)
{
	if (p.get_curr() == nullptr|| p.get_curr()->succ== nullptr)
		return end();

	Link<T>* curr = p.get_curr();
	Link<T>* link_to_erase = curr->succ;
	curr->succ = link_to_erase->succ;

	delete link_to_erase;
	return iterator{ curr->succ };
}
template<typename T>
SList<T>::SList()
	:first{ nullptr }
{
}
template<typename T>
SList<T>::SList(SList<T>&& ll)
	: first{ ll.first }
{
	ll.first = nullptr;
}
template<typename T>
SList<T>::~SList()
{
	Link<T>* current = first;
	while (current != nullptr)
	{
		Link<T>* next = current->succ;
		delete current;
		current = next;
	}
	first = nullptr;
}

template<typename T>
void print(SList<T>& l)
{
	cout << "{ ";
	for (auto& v : l)cout << v << ' ';
	cout << "}\n";
}
int main()
try {
	SList<int> sl;
	sl.push_front(3);
	sl.push_front(2);
	sl.insert(sl.end(),4);
	sl.erase(sl.begin());
	//sl.pop_front();
	//sl.insert_after(sl.begin(), 5);
	//print(sl);
	//sl.erase(++sl.begin());
	//sl.erase_after(++sl.begin());
	print(sl);
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
//Magyar Máté

#include <iostream>
#include <string>

using namespace std;

//Átemelve a refcount0[12].cc fájlból innentõl ->
class Person
{
	int age;
	string name;

public:
	Person(char* pName, int age) : name(pName), age(age) {}
	void display()
	{
		cout << "Name = " << name << "  Age = " << age << endl;
	}
	~Person()
	{
		cout << "Person destructor called" << endl;
	}
};
// <- idáig.

template <typename T>
class RLptr
{
public:
	explicit RLptr(T* object = 0) : pData(object), prev(nullptr), next(nullptr) {}

	RLptr(RLptr& other) {
		pData = other.pData;
		other.insert(this);
	}

	~RLptr() {
		removeThis();
	};

	void display() { 
		if (pData) pData->display();
		else cout << "NULL";
	}

// Copypasta refcount0[12].cc-ból ->
	T& operator* () const throw()
	{
		return *pData;
	}

	T* operator-> () const throw()
	{
		return pData;
	}

	T* get() const throw()
	{
		return pData;
	}
// <- eddig

	RLptr& operator=(RLptr& other) {
		if (other.pData == this->pData) {
			insert(&other);
		}
		else {
				removeThis();
				this->pData = other.pData;
				other.insert(this);
		}

		return other;
	}

	void insert(RLptr* other) {
		if (pData == other->pData) {
			other->prev = this;
			other->next = this->next;
			this->next = other;
		}
	}

	void removeThis() {
		if (prev == nullptr && next == nullptr) delete pData;
		if (next) next->prev = prev;
		if (prev) prev->next = next;
		
	}

private:
	T*     pData;
	RLptr* prev;
	RLptr* next;
};



//Test
int main()
{
	RLptr<Person> p(new Person("Scott", 25));
	cout << "p is: "; p->display();
	cout << "p obj. address: " << p.get() << endl;
	{
		RLptr<Person> q = p;
		cout << "q is: "; q->display();
		cout << "q obj. address: " << q.get() << endl;
		RLptr<Person> r(new Person("Thomas", 33));
		cout << "r is: "; r->display();
		cout << "r obj. address: " << r.get() << endl;
		r = p;
		cout << "after r = p" << endl;
		cout << "r obj. address: " << r.get() << endl;
		cout << "p obj. address: " << p.get() << endl;
		cout << "r is: "; r->display();
		RLptr<Person> s;
		RLptr<Person> t;
		t = s;
		cout << "t obj. address: " << t.get() << endl;
		cout << "s obj. address: " << s.get() << endl;
		t = r;
		cout << "after t = r" << endl;
		cout << "t obj. address: " << t.get() << endl;
		cout << "s obj. address: " << s.get() << endl;
		cout << "r obj. address: " << r.get() << endl;
	}
	p->display();
	return 0;
}
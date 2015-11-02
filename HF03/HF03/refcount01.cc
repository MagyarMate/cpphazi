// refcount01.cc: referencia számlálás egy implementációja
#include<iostream>

using namespace std;

class Person
{
    int age;
    string name;

   public:
     Person(char* pName, int age): name(pName), age(age) {}
     void display()
     {
        cout <<"Name = " << name << "  Age = " << age << endl;
     }
     ~Person()
     {
       cout << "Person destructor called" << endl;
     }
};

class RefCount
{
  private:
    unsigned count; // Reference count
  public:
    void addRef()
    {
      // Increment the reference count
      count++;
    }
    unsigned release()
    {
    // Decrement the reference count and
    // return the reference count.
      return --count;
    }
    unsigned get() const
    {
		  return count;
	  }
};


template < typename T > class RCptr
{
  private:
    T*    pData;       // pointer
    RefCount* pReference; // Reference count

  public:
    explicit RCptr(T* pValue=0) : pData(pValue), pReference(0)
    {
      if (pData)
      {
         // Create a new reference
         pReference = new RefCount();
         // Increment the reference count
         pReference->addRef();
      }
    }

    RCptr(const RCptr<T>& sp) : pData(sp.pData), pReference(sp.pReference)
    {
      // Copy constructor
      // Copy the data and reference pointer
      // and increment the reference count
      if (pReference) pReference->addRef();
    }

    ~RCptr()
    {
      // Destructor
      // Decrement the reference count
      // if reference become zero delete the data

      cout << "RCptr destructor called, pointing to: " << pData << endl;
      if(pReference && pReference->release() == 0)
      {
        delete pData;
        delete pReference;
      }
    }

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


    RCptr<T>& operator = (const RCptr<T>& sp)
    {
      // Assignment operator
      if (this != &sp) // Avoid self assignment
      {
        // Decrement the old reference count
        // if reference become zero delete the old data
        if(pReference && pReference->release() == 0)
        {
          delete pData;
          delete pReference;
        }

       // Copy the data and reference pointer
       // and increment the reference count
       pData = sp.pData;
       pReference = sp.pReference;
       if (pReference) pReference->addRef();
     }
     return *this;
   }

   unsigned getCount() const
	 {
	   return ( pReference ? pReference->get() : 0 );
	 }
};

int main()
{
  RCptr<Person> p(new Person("Scott", 25));
  p->display();
  cout << "p count= " << p.getCount() << endl;
  {
    RCptr<Person> q = p;
    q->display();
    cout << "p count= " << p.getCount() << endl;
    cout << "q count= " << q.getCount() << endl;
    RCptr<Person> r(new Person("Thomas", 33));
    r->display();
    cout << "r count= " << r.getCount() << endl;
    r = p;
    cout << "after r = p"  << endl;
    cout << "p count= " << p.getCount() << endl;
    cout << "r count= " << r.getCount() << endl;
    r->display();
    RCptr<Person> s;
    RCptr<Person> t;
    t=s;
  // Destructor of t will be called here..
  // Destructor of s will be called here..
  // Destructor of r will be called here..
  // Destructor of q will be called here..
  }
  p->display();
  cout << "p count= " << p.getCount() << endl;

  return 0;
// Destructor of p will be called here
// and person pointer will be deleted
}

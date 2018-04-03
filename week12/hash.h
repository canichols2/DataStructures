/***************************************
 * CLASS : HASH 
 * Purely Abstract class
 * Cannot be instanciated on it's own.
 * -------------------------------------
 * IMPLEMENTATION:
 *    uh....
 ***************************************/
#define CONTAINER BST
#include "list.h"
#include "bst.h"
using namespace std;

template <class T>
class Hash
{
private:
   CONTAINER<T>* _bucket;
   int _size;
   int _capacity;
   void copy(const Hash & rhs);
public:
   Hash(int numBuckets)
   {
      _bucket = new CONTAINER<T>[numBuckets];
      _capacity = numBuckets;
      _size = 0;
      // _bucket
   }
   
   //Copy Constructor
   Hash(const Hash & rhs)
   {
      copy(rhs);
   }

   ~Hash()
   {
      // delete [] _bucket;
      clear();
   }

   //Assignment Operator, Just calls copy constructor.
   void operator=(const Hash & rhs)
   {
      if(_size > 0)
         clear();
      copy(rhs);
      // *this = Hash(rhs);
   }

   //Simple In-Line declarations
   bool empty()            {return _size == 0;}
   int  size()const        {return _size;}
   int  capacity() const   {return _capacity;}
   void display()
   {
      int maxLength;
      int totalEmpty;

      for(int i = 0; i < _capacity; i++)
      {
         if(_bucket[i].size() > maxLength)
            maxLength = _bucket[i].size();
         if(_bucket[i].empty())
            totalEmpty++;
      }
      

      for(int i = 0; i < _capacity; i++)
      {
         cout << "[";
         if(i<10) cout << 0;
         cout <<  i  <<"]: ";
         int len = _bucket[i].size();
         for(int i = 0; i < len; i++)
         {
            cout << "=";
         }
         cout << endl;
      }
      cout << "Size:  " << _size       << endl;
      cout << "Max:   " << maxLength   << endl;
      cout << "Empty: " << totalEmpty  << endl;
   }

   
   //external declarations.
   bool find(const T&val);
   void clear();
   void insert(const  T&val);

   //Virtual Method
   virtual int hash(const T & val) const = 0;
};

template <class T>
bool Hash<T>::find(const T&val)
{
   int index = hash(val);
   return _bucket[index].find(val) != NULL;
}

template <class T>
void Hash<T>::clear()
{
   if(_bucket != NULL)
      delete [] _bucket;
}

template <class T>
void Hash<T>::insert(const T&val)
{
   int index = hash(val);
   _bucket[index].insert(val);
   _size++;
}

template <class T>
void Hash<T>::copy(const Hash & rhs)
{
   // clear();
   _bucket = new CONTAINER<T>[rhs._capacity];
   _capacity = rhs._capacity;
   _size = rhs._size;

   //Use list copy constructor
   for(int i = 0; i < _capacity; i++)
   {
      _bucket[i] = CONTAINER<T>(rhs._bucket[i]);
   }
}
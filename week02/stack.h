/***********************************************************************
* Header:
*    Stack
* Summary:
*    This class contains the notion of a stack: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the stack, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Stack         : A class that holds stuff
*        StackIterator : An interator through Stack
* Author
*    Br. Helfrich
************************************************************************/

#ifndef STACK_H
#define STACK_H
// using namespace std;
#include <cstddef>
#include <iostream>
#include <cassert>

// forward declaration for StackIterator
template <class T>
class StackIterator;

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Stack?
   int cap;           // how many items can I put on the Stack before full?
public:
   // default constructor : empty and kinda useless
   Stack() : numItems(0), cap(0), data(NULL) {}
   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);   
   // non-default constructor : pre-allocate
   Stack(int capacity) throw (const char *);
   // destructor : free everything
   ~Stack()           { if (cap) delete [] data;       }
   
   // is the stack currently empty
   bool empty() const  { return numItems == 0;         }
   // remove all the items from the stack
   void clear()        { numItems = 0;                 }
   // how many items are currently in the stack?
   int size() const    { return numItems;              }
   int capacity()      { return cap;                   }

   void push(T t);
   void pop() throw (const char *);
   T& top() throw (const char *);
   void operator=(const Stack<T>& rhs);
};

/**************************************************
 * STACK ITERATOR
 * An iterator through Stack
 *************************************************/
template <class T>
class StackIterator
{
  public:
   // default constructor
  StackIterator() : p(NULL) {}

   // initialize to direct p to some item
  StackIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const StackIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   StackIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   StackIterator <T> operator++(int postfix)
   {
      StackIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
    //   cap = rhs.cap;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for Stack";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for Stack";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the stack by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}
// the functions I added
template <class T>
T& Stack<T>::operator[](const int i){ 
   if(i > cap || i < 0)
      throw "ERROR: index out of bounds";
   return data[i];
}
template <class T>
T& Stack<T>::operator[](const int i)const{ 
   if(i > cap || i < 0)
      throw "ERROR: index out of bounds";
   return data[i];
}
template <class T>
void Stack<T>::push(T t)
{
   if (cap == 0)
   {
         cap = 1;
      // Add 1 to capacity.
      try
         {
            data = new T[cap];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate buffer for Stack";
         }
      //  data = new T[1];
   }
   if (cap == numItems)
   {
      T * temp;
      // double capacity
      cap *= 2;
      try
         {
            temp = new T[cap];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate buffer for Stack";
         }
      for(int i=0;i < numItems;i++)
         temp[i] = data[i];
      //  std::cout << "deleting data now/n";
      delete [] data;
      //  std::cout << "deleted data/n";
      data = temp;
   }
   data[numItems++] = t;
}
template <class T>
void Stack<T>::operator=(const Stack<T> & rhs)
{ 
   //    std::cout << "inside my assignment operator\n";
      if (cap){
         delete [] data;
      }
   numItems = rhs.size();
   cap = rhs.cap;
   if(cap){
      try
         {
               data = new T[cap];
         }
         catch (std::bad_alloc)
         {
               throw "ERROR: Unable to allocate buffer for Stack";
         }
      //  std::cout << numItems << std::endl;
      for(int i=0;i<numItems;i++)
         data[i] = rhs[i];
   }
   //   return *this;
}

template <class T>
void Stack<T>::pop()
{
   if (numItems){
      numItems--;
   }else{
      throw "ERROR: Unable to pop from an empty Stack";
   }
}

template <class T>
T& Stack<T>::top()
{
   if (numItems){
      numItems--;
   }else{
      throw "ERROR: Unable to reference the element from an empty Stack";
   }
   return data[numItems];
}
#endif // STACK_H


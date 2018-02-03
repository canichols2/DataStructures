/***********************************************************************
* Header:
*    Deque
* Summary:
*    This class contains the notion of a deque: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the deque, set, deque, deque, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Deque         : A class that holds stuff
*        DequeIterator : An interator through Deque
* Author
*    Cody Nichols
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H
// using namespace std;
#include <cstddef>
#include <iostream>
#include <cassert>

// forward declaration for DequeIterator
template <class T>
class DequeIterator;

/************************************************
 * DEQUE
 * A class that holds stuff to be accessed from both sides
 ***********************************************/
template <class T>
class Deque
{
 private:
   T *data;      // dynamically allocated array of T
   int numItems; // how many items are currently in the Deque?
   int cap;      // how many items can I put on the Deque before full?
   int _front;     // _front of the line index
   int _back;      // _back of the line index
 public:
   // default constructor : empty and kinda useless
   Deque() : numItems(0), cap(0),_front(0),_back(-1), data(NULL) {}
   // copy constructor : copy it
   Deque(const Deque &rhs) throw(const char *);
   // non-default constructor : pre-allocate
   Deque(int capacity) throw(const char *);
   // destructor : free everything
   ~Deque()   { if (cap) delete[] data; } 
   // is the deque currently empty
   bool empty() const { return numItems == 0; }
   // how many items are currently in the deque?
   int size() const { return numItems; }
   int capacity() { return cap; }

   /*****
    * function for other not in line function
    *****/
   void clear();
   void push(T t);
   void pop() throw(const char *);
   T &front() throw(const char *);
   T &back() throw(const char *);
   Deque<T> &operator=(const Deque<T> &rhs);
};

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque<T>::Deque(const Deque<T> &rhs) throw(const char *)
{
   assert(rhs.cap >= 0);

   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = _front = numItems = 0;
      _back = -1;
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
      throw "ERROR: Unable to allocate buffer for Deque";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;
   _front = 0;

   // copy the items over one at a time using the assignment operator
   for (int i = 0 ; i < numItems; i++){
      int ri = (i + rhs._front) % rhs.cap;
      data[i] = rhs.data[ri];
      _back = i;
   }
      

   // the rest needs to be filled with the default value for T
   // for (int i = numItems; i < cap; i++)
   //    data[i] = T();
}

/**********************************************
 * DEQUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the deque to "capacity"
 **********************************************/
template <class T>
Deque<T>::Deque(int capacity) throw(const char *)
{
   assert(capacity >= 0);

   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer for Deque";
   }

   // initial value stuff
   cap = capacity;
   numItems = 0;
   _front = 0;
   _back = -1;

   // initialize the deque by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}
// the functions I added

/*****************************************************
 * Push: 
 * Add to top of deque
 *****************************************************/
template <class T>
void Deque<T>::push(T t)
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
         throw "ERROR: Unable to allocate buffer for Deque";
      }
   }
   if (cap == numItems)
   {
      T *temp;
      // double capacity
      try
      {
         temp = new T[cap * 2];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer for Deque";
      }
      for (int i = 0; i < numItems; i++){
         int ri = (i + _front) % cap;
         temp[i] = data[ri];
      }
      cap *= 2;
      _front = 0;
      _back = numItems-1;
      delete[] data;
      data = temp;
   }
   _back = (_back + 1) % cap;
   data[_back] = t;
   numItems++;
}

/*****************************************************
 * Assignment Operator Overload
 * Copy deque to new object
 *****************************************************/
template <class T>
Deque<T> &Deque<T>::operator=(const Deque<T> &rhs)
{
   if (cap)
   {
      delete[] data;
   }
   numItems = rhs.size();
   cap = rhs.cap;
   _front = 0;
   _back = rhs.numItems-1;
   if (cap)
   {
      try
      {
         data = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer for Deque";
      }
      for (int i = 0 ; i < numItems; i++){
         int ri = (i + rhs._front) % rhs.cap;
         data[i] = rhs.data[ri];
         _back = i;
      }
   }
   return *this;
}

/*****************************************************
 * pop: 
 * Remove item from top of deque
 *****************************************************/
template <class T>
void Deque<T>::pop() throw(const char *)
{
   if (numItems)
   {
      numItems--;
      _front = (_front + 1)%cap;
   }
   else
   {
      throw "ERROR: attempting to pop from an empty deque";
   }
}

/*****************************************************
 * front: 
 * Return element reference from top of deque
 *****************************************************/
template <class T>
T &Deque<T>::front() throw(const char *)
{
   if (numItems)
   {
      return data[_front];
   }
   else
   {
      throw "ERROR: attempting to access an item in an empty deque";
   }
}
/*****************************************************
 * back: 
 * Return element reference from top of deque
 *****************************************************/
template <class T>
T &Deque<T>::back() throw(const char *)
{
   if (numItems)
   {
      return data[_back];
   }
   else
   {
      throw "ERROR: attempting to access an item in an empty deque";
   }
}
/*****************************************************
 * clear: 
 * empty's the deque. the ride closed down and the guests
 * just left.
 *****************************************************/
template <class T>
void Deque<T>::clear() 
{
 numItems=0;
 _front=0;
 _back=-1;
}
#endif // DEQUE_H

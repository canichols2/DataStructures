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
   Deque() : numItems(0), cap(0),_front(0),_back(0), data(NULL) {}
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
   void realloc();
   void clear();
   void push_front(T t);
   void push_back(T t);
   void pop_front() throw(const char *);
   void pop_back() throw(const char *);
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
      _back = 0;
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
   }
   _back = numItems;
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
   _back = 0;

   // initialize the deque by calling the default constructor of the type...
   // got rid of it because if type was int or something, it would crash. probably.
   // since it doesn't have an int default constructor
   // for (int i = 0; i < capacity; i++)
   //    data[i] = T();
}
// the functions I added
template <class T>
void Deque<T>::realloc()
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
         throw "ERROR: Unable to allocate a new buffer for deque";
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
         throw "ERROR: Unable to allocate a new buffer for deque";
      }
      for (int i = 0; i < numItems; i++){
         int ri = (i + _front) % cap;
         temp[i] = data[ri];
      }
      cap *= 2;
      _front = 0;
      _back = numItems;
      delete[] data;
      data = temp;
   }
}
/*****************************************************
 * Push_back: 
 * Add to top of deque
 *****************************************************/
template <class T>
void Deque<T>::push_back(T t)
{
   realloc();
   data[_back] = t;
   _back = (_back + 1) % cap;
   numItems++;
}
/*****************************************************
 * Push_front: 
 * Add to top of deque
 *****************************************************/
template <class T>
void Deque<T>::push_front(T t)
{
   realloc();
   _front = (_front - 1+cap) % cap;
   data[_front] = t;
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
   // _back = rhs.numItems-1;
   if (cap)
   {
      try
      {
         data = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Deque";
      }
      for (int i = 0 ; i < numItems; i++){
         int ri = (i + rhs._front) % rhs.cap;
         data[i] = rhs.data[ri];
         _back = (i + 1) % cap;
      }
   }
   return *this;
}

/*****************************************************
 * pop_front: 
 * Remove item from top of deque
 *****************************************************/
template <class T>
void Deque<T>::pop_front() throw(const char *)
{
   if (numItems)
   {
      numItems--;
      _front = (_front + 1)%cap;
   }
   else
   {
      throw "ERROR: unable to pop from the front of empty deque";
   }
}
/*****************************************************
 * pop_back: 
 * Remove item from top of deque
 *****************************************************/
template <class T>
void Deque<T>::pop_back() throw(const char *)
{
   if (numItems)
   {
      numItems--;
      _back = (_back - 1 +cap)%cap;
   }
   else
   {
      throw "ERROR: unable to pop from the back of empty deque";
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
      throw "ERROR: unable to access data from an empty deque";
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
      return data[(_back+cap-1)%cap];
   }
   else
   {
      throw "ERROR: unable to access data from an empty deque";
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
 _back=0;
}
#endif // DEQUE_H

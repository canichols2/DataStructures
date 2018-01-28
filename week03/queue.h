/***********************************************************************
* Header:
*    Queue
* Summary:
*    This class contains the notion of a queue: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the queue, set, queue, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Queue         : A class that holds stuff
*        QueueIterator : An interator through Queue
* Author
*    Br. Helfrich
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H
// using namespace std;
#include <cstddef>
#include <iostream>
#include <cassert>

// forward declaration for QueueIterator
template <class T>
class QueueIterator;

/************************************************
 * QUEUE
 * A class that holds stuff to be accessed from both sides
 ***********************************************/
template <class T>
class Queue
{
 private:
   T *data;      // dynamically allocated array of T
   int numItems; // how many items are currently in the Queue?
   int cap;      // how many items can I put on the Queue before full?
   int _front;     // _front of the line index
   int _back;      // _back of the line index
 public:
   // default constructor : empty and kinda useless
   Queue() : numItems(0), cap(0),_front(0),_back(-1), data(NULL) {}
   // copy constructor : copy it
   Queue(const Queue &rhs) throw(const char *);
   // non-default constructor : pre-allocate
   Queue(int capacity) throw(const char *);
   // destructor : free everything
   ~Queue()   { if (cap) delete[] data; } 
   // is the queue currently empty
   bool empty() const { return numItems == 0; }
   // how many items are currently in the queue?
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
   Queue<T> &operator=(const Queue<T> &rhs);
};

/*******************************************
 * QUEUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue<T>::Queue(const Queue<T> &rhs) throw(const char *)
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
      throw "ERROR: Unable to allocate buffer for Queue";
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
 * QUEUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the queue to "capacity"
 **********************************************/
template <class T>
Queue<T>::Queue(int capacity) throw(const char *)
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
      throw "ERROR: Unable to allocate buffer for Queue";
   }

   // initial value stuff
   cap = capacity;
   numItems = 0;
   _front = 0;
   _back = -1;

   // initialize the queue by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}
// the functions I added

/*****************************************************
 * Push: 
 * Add to top of queue
 *****************************************************/
template <class T>
void Queue<T>::push(T t)
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
         throw "ERROR: Unable to allocate buffer for Queue";
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
         throw "ERROR: Unable to allocate buffer for Queue";
      }
      for (int i = 0; i < numItems; i++){
         int ri = (i + _front) % cap;
         temp[i] = data[ri];
      }
      cap *= 2;
      delete[] data;
      data = temp;
   }
   _back = (_back + 1) % cap;
   data[_back] = t;
   numItems++;
}

/*****************************************************
 * Assignment Operator Overload
 * Copy queue to new object
 *****************************************************/
template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &rhs)
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
         throw "ERROR: Unable to allocate buffer for Queue";
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
 * Remove item from top of queue
 *****************************************************/
template <class T>
void Queue<T>::pop() throw(const char *)
{
   if (numItems)
   {
      numItems--;
      _front = (_front + 1)%cap;
   }
   else
   {
      throw "ERROR: Unable to pop from an empty Queue";
   }
}

/*****************************************************
 * top: 
 * Return element reference from top of queue
 *****************************************************/
template <class T>
T &Queue<T>::front() throw(const char *)
{
   if (numItems)
   {
      return data[_front];
   }
   else
   {
      throw "ERROR: Unable to reference the element from an empty Queue";
   }
}
/*****************************************************
 * _back: 
 * Return element reference from top of queue
 *****************************************************/
template <class T>
T &Queue<T>::back() throw(const char *)
{
   if (numItems)
   {
      return data[_back];
   }
   else
   {
      throw "ERROR: Unable to reference the element from an empty Queue";
   }
}
/*****************************************************
 * clear: 
 * empty's the queue. the ride closed down and the guests
 * just left.
 *****************************************************/
template <class T>
void Queue<T>::clear() 
{
 numItems=0;
 _front=0;
 _back=-1;
}
#endif // QUEUE_H

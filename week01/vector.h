/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a vector: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Br. Helfrich
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H
// using namespace std;
#include <cstddef>
#include <iostream>
#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()           { if (cap) delete [] data;       }
   
   // is the vector currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the vector
   void clear()        { numItems = 0;                 }

   // how many items are currently in the vector?
   int size() const    { return numItems;              }
  

   // add an item to the vector
   void insert(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}

   void push_back(T t);
   int capacity();
   T& operator[](const int i);
   T& operator[](const int i)const;
   void operator=(const Vector<T>& rhs);

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int cap;           // how many items can I put on the Vector before full?
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
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
      throw "ERROR: Unable to allocate buffer for Vector";
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
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
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
      throw "ERROR: Unable to allocate buffer for Vector";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the vector by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * VECTOR :: INSERT
 * Insert an item on the end of the vector
 **************************************************/
template <class T>
void Vector <T> :: insert(const T & t) throw (const char *)
{
   // do we have space?
   if (cap == 0 || cap == numItems)
      throw "ERROR: Insufficient space";
   
   // add an item to the end
   data[numItems++] = t;
}


// the functions I added
template <class T>
int Vector<T>::capacity(){
      return cap;
}
template <class T>
T& Vector<T>::operator[](const int i){ 
   if(i > cap || i < 0)
      throw "ERROR: index out of bounds";
   return data[i];
}
template <class T>
T& Vector<T>::operator[](const int i)const{ 
   if(i > cap || i < 0)
      throw "ERROR: index out of bounds";
   return data[i];
}

template <class T>
   void Vector<T>::push_back(T t)
   {
      if (cap == 0)
      {
          cap = 2;
         // Add 1 to capacity.
         try
            {
               data = new T[cap];
            }
            catch (std::bad_alloc)
            {
               throw "ERROR: Unable to allocate buffer for Vector";
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
               throw "ERROR: Unable to allocate buffer for Vector";
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
   void Vector<T>::operator=(const Vector<T> & rhs){ 
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
                  throw "ERROR: Unable to allocate buffer for Vector";
            }
        //  std::cout << numItems << std::endl;
         for(int i=0;i<numItems;i++)
            data[i] = rhs[i];
      }
    //   return *this;
    }

// template <class T>
// std::ostream& operator << (std::ostream& out, const Vector<T>& v) {
//      for (int i=0;i<v.size();i++){
//          out << v[i];
//      }
//      out << std::endl;
//    }
#endif // VECTOR_H


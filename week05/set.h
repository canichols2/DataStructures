#ifndef SET_H
#define SET_H

#include <cstddef>
#include <iostream>
#include <cassert>
using namespace std;

//Forward Declarations
template <class T>
class SetIterator;

/*****
 * SET
 * A class that holds unique elements
 * **/
template <class T>
class Set
{
   private:
      T *data;
      int numItems;
      int cap;
   public:
            // default constructor : empty and kinda useless
      Set() : numItems(0), cap(0), data(NULL) {}
            // destructor : free everything
      ~Set()           { if (cap) delete [] data;       }
            // is the Set currently empty
      bool empty() const  { return numItems == 0;         }
            // remove all the items from the Set
      void clear()        { numItems = 0;                 }
            // how many items are currently in the Set?
      int size() const    { return numItems;              }
            //Capacity allocated
      int capacity()const { return cap;                   }
      
            //Iterators..........
      SetIterator <T> end() { return SetIterator<T>(data + numItems);}
      SetIterator <T> begin() { return SetIterator<T>(data); }

      /****
       * Functions not inline
      ****/
               Set(const Set & rhs) throw (const char *);
               Set(int capacity)    throw (const char *);
      void     insert(T t);
      void     erase(int index);
      int      find(T t);
      void     realloc();
      Set<T>&  operator&& ( Set<T> &rhs);
      Set<T>&  operator|| ( Set<T> &rhs);
      T&       operator[] ( int i);
      T&       operator[] (const int i)const;
      void     operator=  (const Set<T>& rhs);

};

/**************************************************
 * Set ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
  SetIterator() : p(NULL) {}

   // initialize to direct p to some item
  SetIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * Set :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
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
      throw "ERROR: Unable to allocate buffer for Set";
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
 * SET : NON-DEFAULT CONSTRUCTOR
 * Preallocate the set to "capacity"
 **********************************************/
template <class T>
Set <T> :: Set(int capacity) throw (const char *)
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
      throw "ERROR: Unable to allocate buffer for Set";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the Set by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}


/****
 * Functions not inline
****/

/***************************
 * SET: Insert
 * Add items to set and sort
 * *************************/
template <class T>
void  Set<T>::insert(T t){
   if(numItems == 0){
      if(cap == numItems)
         realloc();   
      data[0] = t;
      numItems++;
      return;

   }
   int index = find(t);
   if(index < 0){
      if(cap == numItems){
         realloc();
      }
      index *= -1;
      //Index was 0 so i had rturned numItems
      //convert it back to index 0
      if(index > numItems){
         index = 0;
      }
      
      T swap1 = data[index];
      T swap2;
      data[index] = t;
      for (int i = index + 1; i <= numItems; i++){
         swap2    = data[i];
         data[i]  = swap1;
         swap1    = swap2;
      }
      numItems++;
   }
}
/***************************
 * SET: Erase
 * remove an item from the set
 * *************************/
template <class T>
void  Set<T>::erase(int index){
   for (int i = index;i<numItems;i++){
      data[i] = data[i+1];
   }
   numItems--;
}

/***************************
 * SET: Realloc
 * Reallocate the set for more
 * space when needed.
 * *************************/
template <class T>
void  Set<T>::realloc(){
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
         throw "ERROR: Unable to allocate buffer for Set";
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
         throw "ERROR: Unable to allocate buffer for Set";
      }
      for(int i=0;i < numItems;i++)
         temp[i] = data[i];
   //  std::cout << "deleting data now/n";
      delete [] data;
   //  std::cout << "deleted data/n";
      data = temp;
   }
}

/*******************************************************
 * SET: find
 * returns index of item in set returns negative index
 * of where it would go if it isn't in there
 * returns negative num-items if should go to 0 index.
 * ****************************************************/
template <class T>
int   Set<T>::find(T t){
   if(numItems == 0)
      return -1;
   // iBegin  0
   int iB = 0;
   // iEnd  numElements – 1
   int iE = numItems - 1;
   int iM = (iB + iE)/2;
   // WHILE iBegin ≤ iEnd
   iM = (iB + iE)/2;
   while (iB <= iE){
      if (t == data[iM]){
         return iM;
      }else if(t < data[iM]){
         iE = iM-1;
         iM = (iB + iE)/2;
      }else if(t > data[iM]){
         iB = iM + 1;
         iM = (iB + iE)/2;
      }
   }
   if(t > data[iM]){
      return -(iM + 1);
   }
   if(t < data[iM]){}

   if (iM == 0){
      return (numItems +1) * (-1);
   }
   return -iM;
   // RETURN numElements
}

/***************************
 * SET: &&
 * Intersection Operator
 * Only those in both sets
 * *************************/
template <class T>
Set<T>&    Set<T>::operator&&( Set<T> &rhs)
{
   Set<T>* temp = new Set<T>();
   for(SetIterator<T> it = this->begin(); it != this->end(); ++it){
      if(rhs.find(*it) >= 0){
         temp->insert(*it);
      }
   }
   return *temp;
}

/***************************
 * SET: ||
 * Union Operator
 * Adds 2 sets together and returns new set containing both
 * *************************/
template <class T>
Set<T>&    Set<T>::operator||( Set<T> &rhs)
{
   Set<T>* temp = new Set<T>(rhs);
   for(SetIterator<T> it = this->begin(); it != this->end(); ++it){
      if(rhs.find(*it) < 0){
         temp->insert(*it);
      }
   }
   return *temp;
}


template <class T>
T&    Set<T>::operator[](int i)
{
   return & SetIterator<T>(data + i);
}

template <class T>
T&    Set<T>::operator[](const int i)const
{
   return & SetIterator<T>(data + i);
}

template <class T>
void  Set<T>::operator=(const Set<T>& rhs)
{

}
























#endif
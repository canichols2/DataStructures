#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <iostream>
#include <cassert>
using namespace std;

template <class T>
class ListIterator;
template <class T>
class Node;


template <class T>
class List
{
   private:
      Node<T>* pHead;
      Node<T>* pTail;
      Node<T>* find(Node<T> * ptr, const T &item){
         if(!ptr) return NULL;
         if(ptr->data == item)
            return ptr;
         return find(ptr->pNext,item);
      }
      void hInsert( T item, Node<T>* &ptr, bool headInsert = false){
         if(headInsert || !ptr){
            Node<T>* newPtr = new Node<T>(item,ptr,ptr->pPrev);
            ptr=newPtr;
         }else{
            Node<T>* newPtr = new Node<T>(item,ptr->pNext);
            ptr->pNext=newPtr;
         }
      }
      Node<T>* copy(Node<T>* ptr){
            if(ptr)
               return new Node<T>(
                  ptr->data,
                  copy(ptr->pNext)
               );
            return 0;
            
      }
      void freeData(Node<T>* &ptr){
         if(ptr != NULL){
            freeData(ptr->pNext);
            delete ptr;
         }
         ptr = NULL;
      }
   public:
               List();
               List(List oldList);
               ~List();
      bool     empty();
      void     clear();
      int      size();
      void     push_back(T item);
      void     push_front(T item);
      T        front(){return pHead->data}       // ERROR: unable to access data from an empty list
      T        back(){return pTail->data}
      void     insert(T item,ListIterator it);      // ERROR: unable to allocate a new node for a list
      void     remove();      // ERROR: unable to remove from an invalid location in a list
      Node<T>* begin();
      Node<T>* rbegin();
      Node<T>* end();
      Node<T>* rend();
};

//Constructors: Default constructor (create an empty list) and the copy constructor. If allocation is not possible, the following error will be thrown:
//ERROR: unable to allocate a new node for a list
//Destructor: When finished, the class should delete all the allocated memory.
//operator=(): Removes all the items in the current list and copies the contents from the right-hand side (rhs) onto the current list. In the case of an allocation error, the following c-string will be thrown:
//ERROR: unable to allocate a new node for a list 
//empty(): Test whether the list is empty. This method takes no parameters and returns a Boolean value.
//clear(): Empties the list of all items. There are no parameters and no return value.
//size(): Returns the number of nodes in the list. There are no parameters and the return value is an integer.
//push_back(): Adds an item to the back of the list. This method takes a single parameter (the item to be added to the end of the list) and has no return value. In the case of an allocation error, the following c-string exception will be thrown:
//ERROR: unable to allocate a new node for a list
//push_front(): Adds an item to the front of the list exactly the same as push_back().
//front(): Returns the item currently at the front of the list. This item is returned by-reference, so the last item can be changed through the front() method. If the list is currently empty, the following exception will be thrown:
//ERROR: unable to access data from an empty list
//back(): Returns the item currently at the back of the list exactly the same as front().
//insert(): Inserts an item in the middle of a list. There are two parameters: the data item to be inserted, and a ListIterator pointing to the location in the list where the new item will be inserted before. The return value is an iterator to the newly inserted item. In the case of an allocation error, the following exception will be thrown:
//ERROR: unable to allocate a new node for a list
//remove(): Removes an item from the middle of a list. There is one parameter: a ListIterator pointing to the item to be removed. In the case of an iterator pointing to end(), the following exception will be thrown:
//ERROR: unable to remove from an invalid location in a list
//begin(): Return an iterator to the first element in the list. It takes no parameters and returns a ListIterator.
//rbegin(): Return an iterator to the last element in the list. It takes no parameters and returns a ListIterator. Note that this will behave differently than the STL rbegin() method which returns a std::list <T> :: reverse_iterator.
//end(): Return an iterator referring to the past-the-end element in the list. The past-the-end element is the theoretical element that would follow the last element in the container. It does not point to any element, so it must not be de-referenced.
//rend(): Return an iterator referring to the past-the-front element in the list. The past-the-front element is the theoretical element that would preceed the first element in the container. It does not point to any element, so it must not be de-referenced. Note that this will behave differently than the STL rend() method which returns a std::list <T> :: reverse_iterator.

/**************************************************
 * VECTOR ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class ListIterator
{
  public:
   // default constructor
  ListIterator() : p(NULL) {}

   // initialize to direct p to some item
  ListIterator(T * p) : p(p) {}


   // not equals operator
   bool operator != (const ListIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};






#endif //LIST_H
/***
 * List Class
 * Encapsulates a linked list object.
 * */
#ifndef NODE_H
#define NODE_H
/****
 * NODE
 * A class that holds <T> data and a node<T> pointer
 * */
template <class T>
class Node
{
   public:
      T data;
      Node<T>*pNext;
      Node<T>*pPrev;
      Node():data(NULL),pNext(NULL),pPrev(NULL) {}
      Node(T item):data(item),pNext(NULL),pPrev(NULL) {}
      Node(T item, Node<T>*next):data(item),pNext(next),pPrev(NULL) {}
      Node(T item, Node<T>*next,Node<T>*prev):data(item),pNext(next),pPrev(prev) {}
};

/******
 * Find
 * finds the Node wich matches the given item
 * And returns the NodePtr to that node.
 * */
template <class T>
Node<T>* find(Node<T> * ptr, const T &iteem){
   if(!ptr) return NULL;
   if(ptr->data == item)
      return ptr;
   return find(ptr->pNext,item);
}

/*****
 * Insert
 * Inserts the item in a new node either before or after the NodePtr specified
 * */
template <class T>
void insert( T item, Node<T>* &ptr, bool headInsert = false){
   if(headInsert || !ptr){
      Node<T>* newPtr = new Node<T>(item,ptr);
      ptr=newPtr;
   }else{
      Node<T>* newPtr = new Node<T>(item,ptr->pNext);
      ptr->pNext=newPtr;
   }
}

/****
 * Copy
 * Copy's a linked list
 * each into new nodes, not just pointers. 
 * */
template <class T>
Node<T>* copy(Node<T>* ptr){
      if(ptr)
         return new Node<T>(
            ptr->data,
            copy(ptr->pNext)
         );
      return 0;
      
}

/******
 * freeData
 * removes all items from the linked list (deletes them)
 * */
template <class T>
void freeData(Node<T>* &ptr){
   if(ptr != NULL){
      freeData(ptr->pNext);
      delete ptr;
   }
   ptr = NULL;
}

/*****
 * OStream Extraction Operator
 * Overloading the extraction operator
 * to have it output all of the data 
 * in each Node of the linked lists.
 * */
template<class T>
ostream& operator << (ostream& out, Node<T>* &ptr){
   if(!ptr)return out;
   out << ptr->data;
   if(ptr->pNext != NULL)  
      out << ", " << ptr->pNext;
   return out;
}
#endif //NODE_H
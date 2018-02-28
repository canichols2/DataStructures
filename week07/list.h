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
   private: //Attributes
      Node<T>* pHead;
      Node<T>* pTail;
      int numItems;

   private: //Methods
      Node<T>* find(Node<T> * ptr, const T &item);
      void hInsert( T item, Node<T>* &ptr);
      Node<T>* copy(Node<T>* ptr);
      void freeData(Node<T>* &ptr);
   public:
                           List()   :pHead(NULL),pTail(NULL),numItems(0){}
                           ~List()  {freeData(pHead); numItems = 0;}
      bool                 empty()  {return !numItems;}
      void                 clear()  {freeData(pHead); numItems = 0;}
      int                  size()   {return numItems;}
      T&                   front()  {return pHead->data;}       // ERROR: unable to access data from an empty list
      T&                   back()   {return pTail->data;}
      ListIterator<T>      begin()  {return ListIterator<T>(this->pHead);}
      ListIterator<T>      rbegin() {return ListIterator<T>(this->pTail);}
      ListIterator<T>      end()    {return ListIterator<T>();}
      ListIterator<T>      rend()   {return ListIterator<T>();}
      
      // Non inline functions
                           List(const List<T>&);
      ListIterator<T>      insert(ListIterator<T> it,T item);      // ERROR: unable to allocate a new node for a list
      void                 remove(ListIterator<T> it);      // ERROR: unable to remove from an invalid location in a list
      void                 push_front(T item);
      void                 push_back(T item);
      List<T>&             operator=(const List<T>& rhs);
};

/**
 * Copy Constructor
 * Copy's a list to a new list.
 * */
template <class T>
List<T>::List(const List<T>& oldList){
   numItems = oldList.numItems;
   pHead = copy(oldList.pHead);
   Node<T>* ptr = pHead;
   while (ptr->pNext){
      ptr=ptr->pNext;
   }
   pTail = ptr;
}

/***
 * Assignment Operator Overload.
 * 
 * */
template <class T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
   numItems = rhs.numItems;
   freeData(pHead);
   pHead = copy(rhs.pHead);
   Node<T>* ptr = pHead;
   while (ptr->pNext){
      ptr=ptr->pNext;
   }
   pTail = ptr;
   return *this;
}

/**
 * insert public function
 * Inserts an item in the middle of a list. 
 * There are two parameters: 
 * * the data item to be inserted, and 
 * * a ListIterator pointing to the location in the list where the new item will be inserted before. 
 * The return value is an iterator to the newly inserted item. 
 * In the case of an allocation error, the following exception will be thrown:
 * */
template <class T>
ListIterator<T> List<T>::insert(ListIterator<T> it,T item){      // ERROR: unable to allocate a new node for a list
   Node<T>* tmp = new Node<T>(item);
   if(numItems == 0 || pHead == NULL)
   {
      pHead = tmp;
      pTail = tmp;

   }
   else if(it.p == NULL){
      //insert at tail
      pTail->pNext = tmp;
      tmp->pPrev = pTail;
      pTail = tmp;
   }else if(it.p == pHead){
      //insert at head
      pHead->pPrev = tmp;
      tmp->pNext = pHead;
      pHead = tmp;
   }else{
      //insert in the middle
      tmp->pNext = it.p;
      tmp->pPrev = it.p->pPrev;
      tmp->pNext->pPrev = tmp;
      tmp->pPrev->pNext = tmp;
   }
   numItems++;
}

/**
 * remove function
 * takes an iterator, removes the pointer at 
 * */
template <class T>
void     List<T>::remove(ListIterator<T> it){      // ERROR: unable to remove from an invalid location in a list
   
   if(it.p == NULL)
      throw  "ERROR: unable to remove from an invalid location in a list";

   if(it.p == pHead) pHead = it.p->pNext;
   if(it.p == pTail) pTail = it.p->pPrev;
   if(it.p->pNext) it.p->pNext->pPrev = it.p->pPrev;
   if(it.p->pPrev) it.p->pPrev->pNext = it.p->pNext;
   numItems--;
}

/**
 * BLANK private function
 * BLANK BLANK BLANK
 * */
template <class T>
void     List<T>::push_front(T item)
{
insert(begin(), item);
}

/**
 * BLANK private function
 * BLANK BLANK BLANK
 * */
template <class T>
void     List<T>::push_back(T item)
{
insert(end(), item);
}

/**
 * find private function
 * searches list, returns ptr to node of matching item
 * returns null if not found.
 * */
template <class T>
Node<T>* List<T>::find(Node<T> * ptr, const T &item){
   if(!ptr) return NULL;
   if(ptr->data == item)
      return ptr;
   return find(ptr->pNext,item);
}

/**
 * hInseart private function
 * Inserts item in front (or in back) of a node
 * */
template <class T>
void List<T>::hInsert( T item, Node<T>* &ptr){
   Node<T>* newPtr;
}

/**
 * copy private function
 * Creates new linked list of new nodes
 * Returns the head node.
 * */
template <class T>
Node<T>* List<T>::copy(Node<T>* ptr){
      if(ptr){
         Node<T>* nextNode = copy(ptr->pNext);   //create new Node by calling copy(),
         Node<T>* newNode =  new Node<T>(  
            ptr->data,        //copy data, not data pointer
            nextNode          // set it to current new node next.
         );
         if(newNode->pNext)
            newNode->pNext->pPrev = newNode;
         return newNode;
      }
      return 0;
      
}

/**
 * freeData private function
 * Given the head node of a linked list,
 * It will loop through and delete every node.
 * */
template <class T>
void List<T>::freeData(Node<T>* &ptr){
   if(ptr != NULL){
      freeData(ptr->pNext);
      delete ptr;
   }
   ptr = NULL;
}

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
  ListIterator(Node<T> * p) : p(p) {}
   // not equals operator
   bool operator != (const ListIterator<T> &rhs) const
   {
      //handle cases of null pointers. so it doesn't dereference null pointers.
      if((this->p == NULL && rhs.p == NULL) || (this->p != NULL && rhs.p != NULL)) return false;
      if((this->p == NULL && rhs.p != NULL) || (this->p != NULL && rhs.p == NULL)) return true;
      return rhs.p->data != this->p->data;
   }
   // dereference operator
   T & operator * ()
   {
      return p->data;
   }
   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }
   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      p = p->pNext;
      return tmp;
   }
   // prefix decrement
   ListIterator <T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }
   // postfix decrement
   ListIterator <T> operator--(int postfix)
   {
      ListIterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }
   friend ListIterator<T>  List<T>::insert(ListIterator<T> it,T item);
   friend void             List<T>::remove(ListIterator<T> it);
  private:
   Node<T> * p;
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
      Node(                                  ):data(NULL),pNext(NULL),pPrev(NULL) {}
      Node(T item                            ):data(item),pNext(NULL),pPrev(NULL) {}
      Node(T item, Node<T>*next              ):data(item),pNext(next),pPrev(NULL) {}
      Node(T item, Node<T>*next,Node<T>*prev ):data(item),pNext(next),pPrev(prev) {}
};

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
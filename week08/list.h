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

/*******************************
 * List Class
 * List of nodes. uses linked list
 * User isn't meant to know this
 * uses linked lists, but just uses it
 * like a deque.
 * *******************************/
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
                           ~List()  {clear();}
      bool                 empty()  {return !numItems;}
      void                 clear()  {freeData(pHead); numItems = 0;pTail = NULL;}
      int                  size()   {return numItems;}
      T&                   front()  {return pHead->data;}       // ERROR: unable to access data from an empty list
      T&                   back()   {return pTail->data;}
      ListIterator<T>      begin()  {return ListIterator<T>(this->pHead);}
      ListIterator<T>      rbegin() {return ListIterator<T>(this->pTail);}
      ListIterator<T>      end()    {return ListIterator<T>();}
      ListIterator<T>      rend()   {return ListIterator<T>();}
      
      // Non inline functions
                           List(const List<T>&);
      ListIterator<T>      insert(ListIterator<T> it,T item);// ERROR: unable to allocate a new node for a list
      ListIterator<T>      insertOrdered(T item)    {  insertOrdered(this->begin(),item);    }
      ListIterator<T>      rInsertOrdered(T item)   {  rInsertOrdered(this->rbegin(),item);    }
      ListIterator<T>      insertOrdered(ListIterator<T> it,T item); // ERROR: unable to allocate a new node for a list
      ListIterator<T>      rInsertOrdered(ListIterator<T> it,T item);// ERROR: unable to allocate a new node for a list
      void                 remove(ListIterator<T> it);       // ERROR: unable to remove from an invalid location in a list
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


template <class T>
ListIterator<T>      List<T>::insertOrdered(ListIterator<T> it,T item) 
{
   if(it.p == NULL || item <= *it){
      return insert(it,item);
   }else{
      it++;
      return insertOrdered(it,item);
   }
}
template <class T>
ListIterator<T>      List<T>::rInsertOrdered(ListIterator<T> it,T item)
{

   if(it.p == NULL || item >= *it){
      it++;
      return insert(it,item);
   }else{
      it--;
      return rInsertOrdered(it,item);
   }
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
 * Push_Front function
 * add item to front of list
 * */
template <class T>
void     List<T>::push_front(T item)
{
insert(begin(), item);
}

/**
 * push_back function
 * add item to end of list
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
 * Probably not used, but nice to have.
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
 * Ended up not using. 
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
      if(p != NULL)
         p = p->pNext;
      return *this;
   }
   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      if(p != NULL)
         p = p->pNext;
      return tmp;
   }
   // prefix decrement
   ListIterator <T> & operator -- ()
   {

      if(p != NULL)
         p = p->pPrev;
      return *this;
   }
   // postfix decrement
   ListIterator <T> operator--(int postfix)
   {
      ListIterator tmp(*this);
      if(p != NULL)
         p = p->pPrev;
      return tmp;
   }
   friend ListIterator<T>  List<T>::insert(ListIterator<T> it,T item);
   friend ListIterator<T>  List<T>::insertOrdered(ListIterator<T> it,T item);
   friend ListIterator<T>  List<T>::rInsertOrdered(ListIterator<T> it,T item);
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
#ifndef SET_H
#define SET_H

#include <cstddef>
#include <iostream>
#include <cassert>
using namespace std;

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
      Node():data(NULL),pNext(NULL) {}
      Node(T item):data(item),pNext(NULL) {}
      Node(T item, Node<T>*next):data(item),pNext(next) {}
};

/******
 * Find
 * finds the Node wich matches the given item
 * And returns the NodePtr to that node.
 * */
template <class T>
Node<T>* find(Node<T> * ptr, const T &item){
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
#endif //SET_H
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
      Node()
      {
         data = NULL;
         pNext = NULL;
      }
      Node(T item)
      {
         data = item;
      }
      Node(T item, Node<T>*next)
      {
         data = item;
         pNext = next;
      }
};

template <class T>
Node<T>* find(Node<T> * ptr, const T &item){
   if(ptr == NULL || ptr->data == NULL || ptr->pNext == NULL) return NULL;
   if(ptr->data == item)
      return ptr;
   return find(ptr->pNext,item);
}
template <class T>
void insert( T item, Node<T>* &ptr, bool headInsert = false){
   if(headInsert){
      Node<T>* newPtr = new Node<T>(item,ptr);
      ptr=newPtr;
   }else{
      Node<T>* newPtr = new Node<T>(item,ptr->pNext);
      ptr->pNext=newPtr;
   }
}

#endif //SET_H
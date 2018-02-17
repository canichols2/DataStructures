/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/*****
 * Add
 * Add an item, sorted, into linked list
 * */
template <class T>
void add(Node<T>* &ptr, T &item)
{
   if (ptr != NULL)
   {
      //if item is less than ptr->data
         //add item before ptr
      //if item is greater than or equal to ptr->data
         // call function again....
      if(item < ptr->data)
         insert(item,ptr,true);
      else
         add(ptr->pNext, item);
   }
   else
   {
      // Call insert function with true arg.
      insert(item,ptr,true);
   }
}

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   Node<T>* front=0;
   for (int i = 0; i < num; i++)
   {
      // Node<T>* ptr = front;
      add(front,array[i]);
   }
   int i = 0;
   while (front != NULL){
      array[i] = front->data;
      i++;
      front = front->pNext;
   }
}

#endif // INSERTION_SORT_H

/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator; 
/*********************************************************
 * CopyFunction
 * *******************************************************/
template <class T>
BinaryNode<T>* copyNode(BinaryNode <T> * ptr)
{
   if(ptr)
   {
      //copy data
      BinaryNode<T>* node = new BinaryNode<T>(ptr->data);
      //copy right node
      node->pRight = copyNode(ptr->pRight);
      //copy left node
      node->pLeft = copyNode(ptr->pLeft);
      return node;
   }
   else
      return 0;
}

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // constructor
   BST(): root(NULL){};
   
   // copy constructor
   BST(const BST & rhs);    
   
   ~BST();

   int  size() const  { return empty() ? 0 : root->size(); }   // BinaryNode class needs a size function
   
   
   // determine if the tree is empty
   bool empty() const
   {
      if(root != 0)
         return false;
      else
         return true;
   }

   // remove all the nodes from the tree.  Makes an empty tree.
   void clear()
   {
      clear(root);
   }
   void clear(BinaryNode<T>* &ptr)
   {
      if(ptr)
      {
         clear(ptr->pLeft);
         clear(ptr->pRight);
         delete ptr;
         ptr = 0;
      }
   }

   // overloaded assignment operator
   BST & operator = (const BST & rhs) throw (const char *)
   {
      this->clear();
      this->root = copyNode(rhs.root);
   }
      
   // insert an item
   void insert(const T & t) throw (const char * );

   // remove an item
   void remove(BSTIterator <T> & it);

   // find a given item
   BSTIterator <T> find(const T & t);

   // the usual iterator stuff
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
private:

   BinaryNode <T> * root;
};



/*********************************************************
* copy constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST &rhs)
{
   this->root = copyNode(rhs.root);
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST()
{
   clear(this->root);
}


/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   if(root == NULL)
   {
      root = new BinaryNode<T>(t);
      return;
   }
   BinaryNode<T>* ptr=root;
   while(ptr)
   {
      if(t < ptr->data)
      {
         if(ptr->pLeft == NULL)
         {
            ptr->pLeft = new BinaryNode<T>(t,ptr);
            return;
         }
         ptr = ptr->pLeft;
      }
      else if(t > ptr->data)
      {
         if(ptr->pRight == NULL)
         {
            ptr->pRight = new BinaryNode<T>(t,ptr);
            return;
         }
         ptr = ptr->pRight;
      }
         
   }
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
   BinaryNode<T>*ptr = it.getNode();
   if(ptr)
   if(ptr->pRight && ptr->pLeft)
   {
      //2 Child delete
      //Can't this be done with just it++ and then it.getNode()????????
      BinaryNode<T>*nsn = ptr->pRight;
      while(nsn->pLeft)
      {
         nsn = nsn->pLeft;
      }
      ptr->data = nsn->data;
      remove(++it);

   }
   else if(ptr->pRight || ptr->pLeft)
   {
      BinaryNode<T>* nbn;
      if(ptr->pRight)
         nbn = ptr->pRight;
      else
         nbn = ptr->pLeft;
      //1 Child delete
      if(ptr->data > ptr->pParent->data)
      {
         ptr->pParent->addRight(nbn);
      }
      else
      {
         ptr->pParent->addLeft(nbn);
      }
   }
   else
   {
      //No Child Delete
      if(ptr->data > ptr->pParent->data)
         ptr->pParent->pRight = NULL;
      else
         ptr->pParent->pLeft = NULL;
   }
   delete ptr;
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   // BSTIterator<T> it;
   BinaryNode<T>* ptr = root;
   while (ptr)
   {
      if(t > ptr->data)
      {
         ptr = ptr->pRight;
      }
      else if(t < ptr->data)
         ptr = ptr->pLeft;
      else if(t == ptr->data)
         return BSTIterator<T>(ptr);
   }
   return BSTIterator<T>();

}


/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
      
   return *this;      
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


#endif // BST_H

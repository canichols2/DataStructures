#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:

   //Basic Constructors
   BinaryNode():data(NULL),pLeft(NULL),pRight(NULL),pParent(NULL){}
   BinaryNode(const T& t):data(t),pLeft(NULL),pRight(NULL),pParent(NULL){}
   BinaryNode(const T& t,BinaryNode <T> * pNode):data(t),pLeft(NULL),pRight(NULL),pParent(pNode){}
   ~BinaryNode(){}

   // return size (i.e. number of nodes in tree)
   int size() const
   {
            return 1 +
               (pLeft== NULL? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);

   //Boolean Operatorns

   bool operator >  (const BinaryNode<T> & rhs) const { return data >  rhs.data; }
   bool operator >= (const BinaryNode<T> & rhs) const { return data >= rhs.data; }
   bool operator <  (const BinaryNode<T> & rhs) const { return data <  rhs.data; }
   bool operator <= (const BinaryNode<T> & rhs) const { return data <= rhs.data; }
   bool operator == (const BinaryNode<T> & rhs) const { return data == rhs.data; }
   bool operator != (const BinaryNode<T> & rhs) const { return data != rhs.data; }
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};

/*****************
 * addLeft method.
 * implementation of method 
 * that assigns the node in the left pointer, 
 * and sets the child pointer to this.
 *****************/
template <class T>
void BinaryNode<T>::addLeft (BinaryNode <T> * pNode){
   pLeft = pNode;
   if(pNode == NULL)return;
   pNode->pParent = this;
}

/*****************
 * addRight method.
 * implementation of method 
 * that assigns the node in the Right pointer, 
 * and sets the child pointer to this.
 *****************/
template <class T>
void BinaryNode<T>::addRight (BinaryNode <T> * pNode){
   pRight = pNode;
   if(pNode == NULL)return;
   pNode->pParent = this;
}

/*****************
 * addLeft method.
 * implementation of method that creates a new node, 
 * puts it in the left pointer, 
 * and sets the child pointer to this.
 * ERROR: Unable to allocate a node
 *****************/
template <class T>
void BinaryNode<T>::addLeft (const T & t) throw (const char *){
   try{
      BinaryNode<T> *tmp = new BinaryNode<T>(t);
      addLeft(tmp);
   }
   catch(std::bad_alloc){
      throw "ERROR: Unable to allocate a node";
   }

}

/*****************
 * addRight method.
 * implementation of method that creates a new node, 
 * puts it in the Right pointer, 
 * and sets the child pointer to this.
 * ERROR: Unable to allocate a node
 *****************/
template <class T>
void BinaryNode<T>::addRight (const T & t) throw (const char *){
   try{
      BinaryNode<T> *tmp = new BinaryNode<T>(t,this);
      addRight(tmp);
   }
   catch(std::bad_alloc){
      throw "ERROR: Unable to allocate a node";
   }

}

/**********************
 * delete.
 * Empty's the Node Tree recursively, then delete's itself. 
 * this is an O(2^n)
 * ***********************/
template <class T>
void deleteBinaryTree(BinaryNode<T> * pNode){
   if(pNode != NULL)
   {
      deleteBinaryTree(pNode->pLeft);
      deleteBinaryTree(pNode->pRight);
      delete pNode;
   }
}



#endif // BNODE_H

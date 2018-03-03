/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/
#include <string>
#include "bnode.h"
#include "pair.h"
#include "list.h"
using namespace std;
#ifndef HUFFMAN_H
#define HUFFMAN_H

void huffman(string fileName);




//Temporary non-member functions to output BinaryNode and Pair
template <class T>
ostream & operator << (ostream & out, const BinaryNode<T>* & rhs){
   "  { D:{lBN}{rBN} }  ";
   out << "{"<<rhs->data<<":"<<rhs->pLeft<<":"<<rhs->pRight<<" ";
   // out << rhs->data << " ";
   return out;
}
// Pair<float,string>


/*****************************************
 * LIST :: DISPLAY
 * Display the contents of the list forwards
 ****************************************/
template <class T>
ostream & operator << (ostream & out, List <T> & rhs)
{
   out << '{';

// #ifdef TEST3
   ListIterator <T> it;
   for (it = rhs.begin(); it != rhs.end(); ++it)
      out << "  " << (*it)->data;
// #endif // TEST3

   out << "  }";

   return out;   
}






// class huff
// {
//    private:
//       BinaryNode<pair<float,string>>* bHead;
//       List<BinaryNode<pair<float,string>>*> orderedList;
//       // pair<string,int> keys[];
//    public:
//       huff():bHead(NULL){}
//       huff(BinaryNode<pair<float,string>>* bNode):bHead(bNode){}
      
//       void addNode(BinaryNode<pair<float,string>> bNode){}
//       void getKey(){}
// };









#endif // HUFFMAN_h

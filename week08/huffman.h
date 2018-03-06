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


class huff
{
      private:
         List<BinaryNode<Pair<float,string> >*> orderedList;
         List<Pair<string,string> > endList;
         void readTree(BinaryNode<Pair<float,string> >* node,string huffStr)
         {
            if(node->pLeft != NULL && node->pRight != NULL){
               readTree(node->pLeft,huffStr +"0");
               readTree(node->pRight,huffStr +"1");
            }else{
               // cout << node->data.second << " = " << huffStr<<endl;
               endList.insertOrdered( Pair<string,string>(node->data.second,huffStr));
            }
         }
      public:
      huff():orderedList(){}
      friend ostream & operator << (ostream & out, huff & rhs) {
		  out << "Huff Ordered List: ";
		  out << '{';
		  ListIterator <BinaryNode<Pair<float, string > >*> it;
		  for (it = rhs.orderedList.begin(); it != rhs.orderedList.end(); ++it)
			  out << "  " << (*it)->data;
		  out << "  }";
		  return out;
	  }
      void createTree(){
         // cerr << "Creating Tree"<<endl; 
         while (orderedList.size() > 1)
         {
               string tmpStr = "";
               BinaryNode<Pair<float,string> >* tmp1 =orderedList.front();      orderedList.remove(orderedList.begin());
               BinaryNode<Pair<float,string> >* tmp2 =orderedList.front();      orderedList.remove(orderedList.begin());
               BinaryNode<Pair<float,string> >* node = 
               new BinaryNode<Pair<float,string> >(
                     Pair<float,string>(tmp1->data.first +tmp2->data.first,tmpStr)
                     );
               node->addLeft(tmp1);
               node->addRight(tmp2);
               rInsertOrdered(node);
               // cout << *this<<endl;
         }
      }
      void readTree()
      {
         readTree(orderedList.front(),"");
         for(ListIterator<Pair<string,string> > it = endList.begin(); it != NULL; it++)
         {
            cout << (*it).first << " = " << (*it).second<<endl;
         }
      }

      /***************************
       * Insert Ordered. 
       * Needed because the function in
       * the List object doesnt' work
       * if the list contains object pointers
       * ****************************/
      ListIterator<BinaryNode<Pair<float,string> >*> insertOrdered(BinaryNode<Pair<float,string> >* item){
            return insertOrdered(orderedList.begin(),item);
      }
      ListIterator<BinaryNode<Pair<float,string> >*> insertOrdered(ListIterator<BinaryNode<Pair<float,string> >*> it,BinaryNode<Pair<float,string> >* item) 
      {
            if(
               !(
               it != NULL) || 
               item->data <= (*it)->data)
            {
                  return orderedList.insert(it,item);
            }else{
                  it++;
                  return insertOrdered(it,item);
            }
      }
      ListIterator<BinaryNode<Pair<float,string> >*> rInsertOrdered(BinaryNode<Pair<float,string> >* item){
            return rInsertOrdered(orderedList.rbegin(),item);
      }
      ListIterator<BinaryNode<Pair<float,string> >*> rInsertOrdered(ListIterator<BinaryNode<Pair<float,string> >*> it,BinaryNode<Pair<float,string> >* item)
      {
            if(!(it != NULL)){
               it = orderedList.begin();
               return orderedList.insert(it,item);
            } else if(item->data >= (*it)->data){
               it++;
               return orderedList.insert(it,item);
            }else{
               it--;
               return rInsertOrdered(it,item);
            }
      }


};








//Temporary non-member functions to output BinaryNode and Pair

template <class T>
ostream & operator << (ostream & out, BinaryNode<T>* & rhs){
   // "  { D:{lBN}{rBN} }  ";
   // out << "{"<<rhs->data<<":"<<rhs->pLeft<<":"<<rhs->pRight<<" ";
   if(rhs != NULL)
      out <<rhs->pLeft<<rhs->data<<" "<<rhs->pRight;
   return out;
}


/*****************************************
 * LIST :: DISPLAY
 * Display the contents of the list forwards
 ****************************************/

// ostream & operator << (ostream & out, List<BinaryNode<Pair<float, string> >*> & rhs)
// {
//    out << '{';
//    ListIterator <BinaryNode<Pair<float,string > >*> it;
//    for (it = rhs.begin(); it != rhs.end(); ++it)
//       out << "  " << (*it)->data;
//    out << "  }";

//    return out;   
// }

//
//ostream & operator << (ostream & out, huff & rhs){
//   out << "Huff Ordered List: ";
//   out << '{';
//   ListIterator <BinaryNode<Pair<float,string > >*> it;
//   for (it = rhs.orderedList.begin(); it != rhs.orderedList.end(); ++it)
//      out << "  " << (*it)->data;
//   out << "  }";
//   return out;
//}

#endif // HUFFMAN_h

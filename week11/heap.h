/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   <Your Name>   
* Summary: 
*
************************************************************************/
#include <vector>
#include <cmath>
using namespace std;

template <class T>
class Heap;


template <class T>
ostream& operator<<(ostream & out, vector<T> &vect)
{
   out << "{ ";
   for(int i = 0; i < vect.size(); i++)
   {
      out<<vect[i] << " ";
   }
   out << "}";
   
   return out;
}


template<class T>
class Heap
{
   private:
      vector<T> HP;
      int size;
   public:
      Heap()
      {
         this->HP.push_back(T());
         this->size = 0;
      }

      void add(T val)
      {
         this->size += 1;
         this->HP.push_back(val);
         this->orderUp(this->size);
      }
      
      void orderUp(int index)
      {
         if(index <= 1)
            return;
         if (this->HP[index] > this->HP[index / 2])
         {
            swap(index, index / 2);
            this->orderUp(index / 2);
         }
      }

      void orderDown(int index)
      {
         if(this->hasRightChild(index))     //Has both children present
         {
            if(HP[index*2] > HP[index*2+1]) //Left is larger
            {
               if(HP[index] < HP[index*2])
               {
                  swap(index,index*2);
                  orderDown(index*2);
               }
            }
            else                            //Right is larger
            {
               if(HP[index] < HP[index*2+1])  
               {
                  swap(index,index*2+1);
                  orderDown(index*2+1);
               }
            }
         }
         else if(this->hasLeftChild(index))
         {
               if(HP[index] < HP[index*2])
               {
                  swap(index,index*2);
                  orderDown(index*2);
               }
         }
         
      }

      //Single line helper functions. to keep other functions cleaner
      bool hasBothChildren(int index)     {  return hasRightChild(index);       }
      bool hasLeftChild(int index)        {  return (index*2 <= this->size);       }
      bool hasRightChild(int index)       {  return (index * 2 + 1 <= this->size); }
      bool largerThanLeftChild(int index) {  return HP[index] > HP[index*2]   ;   }
      bool largerThanRightChild(int index){  return HP[index] > HP[index*2+1] ;   }

      void sort(vector<T> &vect)
      {
         vect.clear();
         vector<T> tempV;
         // cout << this << endl;
         while(size)
            tempV.push_back( this->pop() );
         // cout << this << endl;
         // cout << tempV << endl;
         // vector<T> orderedV;
         // cout << vect << endl;
         for(int i = tempV.size() - 1; i >= 0; i--)
         {
            T tempT = tempV[i];
            vect.push_back( tempT );
         }
         

      }
      T    pop()
      {
         T tmp;
         swap(1,this->size);
         this->size -= 1;
         tmp = HP.back();
         HP.pop_back();

         //OrderDown...
         orderDown(1);

         return tmp;
      }
      void swap(int index1,int index2)
      {
         T  tmp     = HP[index1];
         HP[index1] = HP[index2];
         HP[index2] = tmp;
      }

};


/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> &data)
{
   Heap<T> heap;
   for(int i = 0; i < data.size(); i++)
   {
      heap.add(data[i]);
   }
   heap.sort(data);
   // cout << "heapSort(): data: " << data << endl;
}

#ifndef WHOLE
#define WHOLE
#include <iostream>
// #include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;

// template <class T>
class WholeNumber
{
   private:
      int number;
   public:
      WholeNumber():number(0){}
      WholeNumber(int num):number(num){}
      WholeNumber(const WholeNumber& num){
         this->number = num.number;
      }
      WholeNumber& operator+=(const WholeNumber& rhs){
         number += rhs.number;
         return *this;
      }
      WholeNumber& operator=(const WholeNumber& rhs){
         number = rhs.number;
         return *this;
      }
      WholeNumber operator+(const WholeNumber& rhs){
         WholeNumber tmp = *this;
         tmp += rhs;
         return tmp;
      }
      friend ostream& operator << (ostream& out,const  WholeNumber &rhs);
};


ostream& operator << (ostream& out,const  WholeNumber &rhs)
{
   out <<rhs.number;
   return out;
}
#endif
/****************************************************
 * Pure abstract classes that I will use as interfaces
 ****************************************************/
#ifndef prnt
#define prnt
/* code */

#include <string>
class Printable
{
   public:
      Printable(){}
      virtual ~Printable(){}
      virtual std::string toString()=0;
};
#endif //prnt
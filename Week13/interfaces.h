/****************************************************
 * Pure abstract classes that I will use as interfaces
 ****************************************************/
#include <string>
class Printable
{
   public:
      Printable(){}
      virtual ~Printable(){}
      virtual std::string toString()=0;
};
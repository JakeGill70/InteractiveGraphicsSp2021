#include "AbstractReader.h"

void AbstractReader::Trim(string& str)
{
   const string delimiters = " \f\n\r\t\v";
   str.erase(str.find_last_not_of(delimiters) + 1);
   str.erase(0, str.find_first_not_of(delimiters));
}

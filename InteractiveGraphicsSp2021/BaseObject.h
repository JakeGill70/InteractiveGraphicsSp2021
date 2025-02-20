#pragma once
#ifndef BASE_OBJECT
#define BASE_OBJECT

#include <sstream>
#include <fstream>
#include <string>
using std::string;
using std::stringstream;
using std::stringstream;
using std::ifstream;

// The base class for everything
class BaseObject
{
private:
   // All objects will have access to the logger
   static stringstream _log;

public:
   inline string GetLog() {
      string log;
      // Send the string stream into a string
      getline(_log, log);
      return log;
   }

   void Log(const string& message) {
      _log << message << "\n";
   }

   void Log(const char* message) {
      _log << message << "\n";
   }
};




#endif


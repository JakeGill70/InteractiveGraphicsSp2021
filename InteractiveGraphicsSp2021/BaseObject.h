#pragma once
#ifndef BASE_OBJECT
#define BASE_OBJECT

#include <sstream>
#include <fstream>
#include <string>
using std::string;
using std::wstring;
using std::stringstream;
using std::stringstream;
using std::ifstream;

// The base class for everything
class BaseObject
{
protected:
   // All objects will have access to the logger
   static stringstream _log;

public:
   inline string GetLog() {
      return _log.str();
   }

   static inline wstring WidenString(const string& str) {
      return wstring(str.begin(), str.end());
   }

   void Log(const string& message) {
      _log << message << "\n";
   }

   void Log(const char* message) {
      _log << message << "\n";
   }
};




#endif


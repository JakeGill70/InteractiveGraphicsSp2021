#pragma once
#ifndef ABSTRACT_READER
#define ABSTRACT_READER

#include "BaseObject.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

class AbstractReader :
    public BaseObject
{
public:
   virtual ~AbstractReader() {}
   virtual void Open() = 0;
   virtual void Read() = 0;
   virtual void Close() = 0;
   virtual bool HasError() = 0;

protected:
   virtual void Trim(string& str);
   virtual void Split(const std::string& s, char delimiter, std::vector<std::string>& tokens);
};

#endif


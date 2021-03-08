#pragma once
#ifndef ABSTRACT_READER
#define ABSTRACT_READER

#include "BaseObject.h"
#include <string>

using std::string;

class AbstractReader :
    public BaseObject
{

protected:
    virtual void Trim(const string& str)=0;

public:
    virtual ~AbstractReader() {};
    virtual void Open() = 0;
    virtual void Read() = 0;
    virtual void Close() = 0;
    virtual bool HasError() = 0;

};

#endif

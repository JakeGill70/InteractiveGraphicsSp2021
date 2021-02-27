#pragma once
#ifndef TEXT_FILE_READER
#define TEXT_FILE_READER

#include "AbstractReader.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

class TextFileReader :
    public AbstractReader
{
protected:
   string _filePath;
   ifstream _fin;
   stringstream _stringBuffer;
   bool _errorOccurred;

public:
   TextFileReader(const string& filePath="") : _errorOccurred(false) {
      SetFilePath(filePath);
   }
   ~TextFileReader() {
      Close();
   }

   virtual inline void SetFilePath(const string& filePath) {
      _filePath = filePath;
   }

   void Open();
   void Read();
   void Close();
   string GetContents();
   bool HasError() { return _errorOccurred; }
};

#endif


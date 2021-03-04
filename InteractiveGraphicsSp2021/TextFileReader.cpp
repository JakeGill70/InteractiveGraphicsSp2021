#include "TextFileReader.h"

void TextFileReader::Open()
{
   _fin.open(_filePath.c_str());
   if (_fin.fail()) {
      _errorOccurred = true;
      char buffer[256];
      strerror_s(buffer, 256, errno);
      Log(buffer);
   }
}

void TextFileReader::Read()
{
   if (_errorOccurred) return;
   string line;
   while (!_fin.eof()) {
      getline(_fin, line);
      Trim(line);
      if (line != "") {
         _stringBuffer << line << std::endl;
      }
   }
}

void TextFileReader::Close()
{
   _fin.close();
}

string TextFileReader::GetContents()
{
   return _stringBuffer.str();
}

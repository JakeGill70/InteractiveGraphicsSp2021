#pragma once
#ifndef TEXT_FILE_READER
#define TEXT_FILE_READER

#include "AbstractReader.h"

class TextFileReader :
	public AbstractReader
{
protected:
	string _filePath;
	ifstream _fin;
	stringstream _stringBuffer;
	bool _errorOccurred;

public:
	TextFileReader();
	TextFileReader(const string& filePath);
	~TextFileReader();
	
	void Open();
	void Read();
	void Close();
	string GetContents();
	bool HasError();
	void SetFilePath(const string& path);
};

#endif

#pragma once
#ifndef ABSTRACT_READER
#define ABSTRACT_READER

#include "BaseObject.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using std::string;

class AbstractReader :
	public BaseObject
{

protected:
	virtual void Trim(string& str) {
		const string delimiters = " \f\n\r\t\v";
		str.erase(str.find_last_not_of(delimiters) + 1);
		str.erase(0, str.find_first_not_of(delimiters));
	}

	virtual void Split(const std::string& s, char delimiter, std::vector<std::string>& tokens) {
		std::string token;
		std::istringstream tokenStream(s);   
		while (std::getline(tokenStream, token, delimiter)) { 
			tokens.push_back(token); 
		}
	}

public:
	virtual ~AbstractReader() {};
	virtual void Open() = 0;
	virtual void Read() = 0;
	virtual void Close() = 0;
	virtual bool HasError() = 0;

};

#endif

#include "TextFileReader.h"


TextFileReader::TextFileReader(const string& filePath = "") : _errorOccurred(false) {
	SetFilePath(filePath);
}

TextFileReader::~TextFileReader() {
	Close();
}

void TextFileReader::SetFilePath(const string& path) {
	_filePath = path;
}

bool TextFileReader::HasError() {
	return _errorOccurred;
}

void TextFileReader::Open() {
	_fin.open(_filePath);
	if (_fin.fail()) {
		_errorOccurred = true;
		_stringBuffer << errno << std::endl;
		Log(_stringBuffer.str());
	}
}

void TextFileReader::Read() {
	if (HasError()) {
		return;
	}

	string line;
	while (!_fin.eof()) {
		std::getline(_fin, line);
		Trim(line);
		if (!line.empty()) {
			_stringBuffer << line << std::endl;
		}
	}
}

void TextFileReader::Close() {
	_fin.close();
}

string TextFileReader::GetContents() {
	return _stringBuffer.str();
}
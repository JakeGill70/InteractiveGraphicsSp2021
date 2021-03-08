#include "TextFileReader.h"


TextFileReader::TextFileReader() : _errorOccurred(false) {
	SetFilePath("");
}

TextFileReader::TextFileReader(const string& filePath) : _errorOccurred(false) {
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

		char buffer[256];   
		strerror_s(buffer, 256, errno);
		_stringBuffer << buffer << std::endl;
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
#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Util.h"

class FNTParser
{
public:

	FNTParser();
	~FNTParser();

	void loadFontFile(const std::string & path, uint8_t flags, int & char_num, int coords[][6], std::string & texture_path);

private:

	void getTexturePath(std::ifstream & stream, std::string & path);
	void getCharNum(std::ifstream & stream, int & num);
	void fillCoordData(std::ifstream & stream, int c_num, int coords[][6]);
};


#include "FNTParser.h"



FNTParser::FNTParser()
{
}

FNTParser::~FNTParser()
{
}


void FNTParser::loadFontFile(const std::string & path, uint8_t flags, int & char_num, int coords[][6], std::string & texture_path)
{
	std::ifstream file;
	file.open(path);
	
	getTexturePath(file, texture_path);
	getCharNum(file, char_num);
	fillCoordData(file, char_num, coords);
}

//SHITCODE ALERT!!! BEWARE OF THE POWER OF TERRIBLE CODE STRUCTURE!

void FNTParser::getTexturePath(std::ifstream & stream, std::string & path)
{
	for (int i = 0; i < 19; i++) //Jump to texture name
		stream.ignore(256, '=');

	stream.ignore(1);
	std::string str;
	char c_str[256];
	stream.get(c_str, 256, '\"');
	str.append(c_str);
	path = str;
}

void FNTParser::getCharNum(std::ifstream & stream, int & num)
{
	stream.ignore(256, '='); //Jump to characters number

	stream >> num;
}

void FNTParser::fillCoordData(std::ifstream & stream, int c_num, int coords[][6])
{

	int rel_pos = stream.tellg();

	int ascii_index;
	
	for (int i1 = 0; i1 < c_num; i1++)
	{
		stream.ignore(256, '=');
		stream >> ascii_index;
		for (int i2 = 0; i2 < 9; i2++)
		{
			if (i2 < 6)
			{
				stream.ignore(256, '=');
				stream >> coords[ascii_index][i2];
			}
			else
			{
				stream.ignore(256, '=');
			}
		}
	}
}
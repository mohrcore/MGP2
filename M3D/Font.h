#pragma once

#include <string>

#include "Util.h"
#include "Texture.h"
#include "TextureBank.h"
#include "FNTParser.h"

class Font
{
public:

	Font(TextureBank & tb);
	~Font();

	void loadFromFile(const std::string & path);

	Rect2d getTexCoordinates(char character);

private:

	FNTParser _f_parser;

	Texture * font_atlas;

	TextureBank & _tb;

	int _coords[256][6];
	int _char_num;
};


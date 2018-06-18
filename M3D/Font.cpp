#include "Font.h"



Font::Font(TextureBank & tb) : _tb(tb)
{
}


Font::~Font()
{
}

void Font::loadFromFile(const std::string & path)
{
	std::string t_str;
	_f_parser.loadFontFile(path, NULL, _char_num, _coords, t_str);
	font_atlas = _tb.getTextureByPath(path.substr(0, path.find_last_of('/', path.size()) + 1) + t_str); //TODO: normal slash should be accepted as well
}

Rect2d Font::getTexCoordinates(char character)
{
	return Rect2d(_coords[character][0], _coords[character][1], _coords[character][2], _coords[character][3]);
}

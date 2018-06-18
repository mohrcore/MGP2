#include "MText.h"



MText::MText()
{
}

MText::~MText()
{
}


void MText::setFont(Font & font)
{
	_font = &font;
}

void MText::setSize(float size)
{
	_size = size;
}

void MText::setThickness(float value)
{
	_thickness = value;
}

void MText::setText(const std::string & text)
{
	_text = text;
}

void MText::setPosition(Vec2f position)
{
	_position = position;
}

Vec2f MText::getPosition()
{
	return _position;
}

void MText::draw()
{
	float v_cursor = 0.0f; //Virtual cursor

	for (int i = 0; i < _text.size(); i++)
	{
		//_rend.renderRect2d(Rect2d, )
	}
}
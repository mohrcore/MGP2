#pragma once

#include <string>

#include "Renderer.h"
#include "Font.h"
#include "Util.h"

class MText
{
public:

	MText();
	~MText();

	void setFont(Font & font);
	void setText(const std::string & text);
	void setSize(float size);
	void setThickness(float value);

	void setPosition(Vec2f position);
	
	Vec2f getPosition();

	void draw();

private:

	Font * _font;

	std::string _text;

	float _size, _thickness;

	Vec2f _position;

	Renderer _rend;
};


#pragma once

#include <string>

#include "Util.h"
#include "Texture.h"
#include "TextureBank.h"

class Sprite
{
public:

	Sprite(TextureBank & tb);
	~Sprite();

	void loadTextureFromFile(const std::string & path);

	void setPosition(Vec2f position);
	void setDimensions(Vec2f dimensions);
	void setCropRect(Rect2d rect);
	void setRepeats(Vec2f rep);
	
	Vec2f getPosition() const;
	Vec2f getDimensions() const;
	Rect2d getRect2d() const;
	Texture * getTexture() const;
	Rect2d getCropRect() const;
	Vec2f getRepeats() const;

private:

	Rect2d _sprite_rect;
	Rect2d _crop_rect;
	Vec2f _repeats;

	Texture * _texture;
	TextureBank & _tb;
};


#include "Sprite.h"



Sprite::Sprite(TextureBank & tb) : _tb(tb), _crop_rect(0.0f, 0.0f, 0.0f, 0.0f), _repeats(0.0f, 0.0f)
{
}

Sprite::~Sprite()
{
}


void Sprite::loadTextureFromFile(const std::string & path)
{
	_texture = _tb.getTextureByPath(path);
}

void Sprite::setPosition(Vec2f position)
{
	_sprite_rect.left = position.x;
	_sprite_rect.top = position.y;
}

void Sprite::setDimensions(Vec2f dimensions)
{
	_sprite_rect.right = dimensions.x;
	_sprite_rect.bottom = dimensions.y;
}

void Sprite::setCropRect(Rect2d rect)
{
	_crop_rect = rect;
}

void Sprite::setRepeats(Vec2f rep)
{
	_repeats = rep;
}

Vec2f Sprite::getPosition() const
{
	return Vec2f(_sprite_rect.left, _sprite_rect.top);
}

Vec2f Sprite::getDimensions() const
{
	return Vec2f(_sprite_rect.right, _sprite_rect.bottom);
}

Rect2d Sprite::getRect2d() const
{
	return _sprite_rect;
}

Texture * Sprite::getTexture() const
{
	return _texture;
}

Rect2d Sprite::getCropRect() const
{
	return _crop_rect;
}

Vec2f Sprite::getRepeats() const
{
	return _repeats;
}
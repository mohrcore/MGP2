#include <SDL.h>

#include "Util.h"

void fatal_error(const std::string message)
{
	std::cout << "Fatal error: " << message << std::endl << std::endl << "Press any key to quit." << std::endl;
	system("pause");
	SDL_Quit();
	exit(1);
}

Vec3f::Vec3f(float px, float py, float pz) : x(px), y(py), z(pz)
{
}

Vec3f::Vec3f()
{
}


Vec3f Vec3f::operator+(const Vec3f & right)
{
	return Vec3f(x + right.x, y + right.y, z + right.z);
}

Vec3f Vec3f::operator-(const Vec3f & right)
{
	return Vec3f(x - right.x, y - right.y, z - right.z);
}

Vec3f & Vec3f::operator+=(const Vec3f & right)
{
	x += right.x;
	y += right.y;
	z += right.z;

	return *this;
}

Vec3f & Vec3f::operator-=(const Vec3f & right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;

	return *this;
}


Vec2f::Vec2f(float px, float py) : x(px), y(py)
{
}

Vec2f::Vec2f()
{
}

Vec2f Vec2f::operator+(const Vec2f & right)
{
	return Vec2f(x + right.x, y + right.y);
}

Vec2f Vec2f::operator-(const Vec2f & right)
{
	return Vec2f(x - right.x, y - right.y);
}

Vec2f & Vec2f::operator+=(const Vec2f & right)
{
	x += right.x;
	y += right.y;

	return *this;
}

Vec2f & Vec2f::operator-=(const Vec2f & right)
{
	x -= right.x;
	y -= right.y;

	return *this;
}


Color::Color(GLubyte cr, GLubyte cg, GLubyte cb, GLubyte ca) : r(cr), g(cg), b(cb), a(ca)
{
}

Color::Color()
{
}


BinaryInput::BinaryInput() : _istate(0)
{
}

void BinaryInput::setInputState(uint8_t bit, bool state)
{
	if (state)
		_istate |= 1 << bit;
	else
		_istate &= ~(1 << bit);
}

bool BinaryInput::getInputState(uint8_t bit)
{
	if (_istate & (1 << bit))
		return true;
	else
		return false;
}

uint64_t BinaryInput::getAllStates()
{
	return _istate;
}


Rect2d::Rect2d() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f)
{
}

Rect2d::Rect2d(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b)
{
}
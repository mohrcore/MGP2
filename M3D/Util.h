#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

#define IS_KEY_LEFT 0
#define IS_KEY_RIGHT 1
#define IS_KEY_UP 2
#define IS_KEY_DOWN 3
#define IS_KEY_W 4
#define IS_KEY_A 5
#define IS_KEY_S 6
#define IS_KEY_D 7

void fatal_error(const std::string message);

struct Vec3f
{
	float x;
	float y;
	float z;

	Vec3f operator+(const Vec3f & right);
	Vec3f operator-(const Vec3f & right);
	Vec3f & operator+=(const Vec3f & right);
	Vec3f & operator-=(const Vec3f & right);

	Vec3f(float px, float py, float pz);
	Vec3f();
};

struct Vec2f
{
	float x;
	float y;

	Vec2f operator+(const Vec2f & right);
	Vec2f operator-(const Vec2f & right);
	Vec2f & operator+=(const Vec2f & right);
	Vec2f & operator-=(const Vec2f & right);

	Vec2f(float px, float py);
	Vec2f();
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	Color(GLubyte cr, GLubyte cg, GLubyte cb, GLubyte ca);
	Color();
};

struct BinaryInput
{
public:

	BinaryInput();

	void setInputState(uint8_t bit, bool state);

	bool getInputState(uint8_t bit);

	uint64_t getAllStates();

private:

	uint64_t _istate;
};


struct Rect2d
{
	Rect2d();
	Rect2d(float l, float t, float r, float b);

	float left, top, right, bottom;
};
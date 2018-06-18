#pragma once

#include <GL/glew.h>
#include <cstdlib>
#include <algorithm>

#include "Util.h"

#define MATRIX_ERROR 'E'

class Mat4
{
public:
	Mat4();
	Mat4(char type);
	Mat4(const Mat4 & arg);
	~Mat4();

	//void create(int dim_n, int dim_m, bool identity); //Creates new Mat4 with m*n dimensions and fills it with zeros, or makes it an identity Mat4 if bool identity equals true
	//void clear(); //Clears all data
	void identity();
	void zero();

	float & operator()(int n, int m); //Can be used as Mat4[0] to pass a pointer to contiguous 2D array (useful for some libraries like GLEW)
	Mat4 operator*(const Mat4 & right); //Mat4 multiplication
	Mat4 operator+(const Mat4 & right); //Mat4 addiction
	Mat4 operator-(const Mat4 & right); //Mat4 substraction
	Mat4 & operator=(const Mat4 arg);
	Mat4 & operator*=(const Mat4 & right); //Mat4 multiplication
	Mat4 & operator+=(const Mat4 & right); //Mat4 addiction
	Mat4 & operator-=(const Mat4 & right); //Mat4 substraction

	//int m();
	//int n();

	bool good();

private:

	GLfloat data[4][4];

	//int _n, _m; ///Mat4 dimensions

	bool error;
};


class TransformationMatrix4
{
public:

	TransformationMatrix4();

	Mat4 scale(Vec3f v);
	Mat4 rotate(Vec3f v);
	Mat4 translate(Vec3f v);

private:

	Mat4 mat;
};


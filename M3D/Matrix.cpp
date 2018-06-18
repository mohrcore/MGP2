#include <cstdlib>
#include <algorithm>

#include "Util.h"

#include "Matrix.h"



Mat4::Mat4() : error(false)
{
	zero();
}

Mat4::Mat4(char type) : error(false)
{
	zero();

	switch (type)
	{
	case MATRIX_ERROR:

		error = true;
		break;
	}
}

Mat4::Mat4(const Mat4 & arg)
{
	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			data[i1][i2] = arg.data[i1][i2];
		}
	}

	error = arg.error;
}


Mat4::~Mat4()
{
	//clear();
}


//void Mat4::create(int dim_n, int dim_m, bool identity)
//{
//	clear();
//
//	data = new float *[dim_n];
//	/*for (int i = 0; i < dim_n; i++)
//		data[i] = new float[dim_m];*/
//
//	data[0] = new float[dim_n * dim_m]; //Creates contiguous 2D array
//	for (int i = 0; i < dim_n; i++)
//	{
//		data[i] = &data[0][i * dim_m];
//	}
//
//	_n = dim_n;
//	_m = dim_m;
//
//	for (int i1 = 0; i1 < dim_n; i1++)
//	{
//		for (int i2 = 0; i2 < dim_m; i2++)
//		{
//			data[i1][i2] = 0;
//		}
//	}
//
//	if (identity)
//	{
//		for (int i1 = 0; i1 < std::min(dim_n, dim_m); i1++)
//		{
//			data[i1][i1] = 1;
//		}
//	}
//}

//void Mat4::clear()
//{
//	if (data != nullptr)
//	{
//		delete[] data[0];
//		delete[] data;
//	}
//}

void Mat4::identity()
{
	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			if (i1 == i2)
				data[i1][i2] = 1.0f;
			else
				data[i1][i2] = 0.0f;
		}
	}
}

void Mat4::zero()
{
	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			data[i1][i2] = 0.0f;
		}
	}
}

//int Mat4::m()
//{
//	return _m;
//}
//
//int Mat4::n()
//{
//	return _n;
//}

bool Mat4::good()
{
	return ~error;
}

float & Mat4::operator()(int n, int m)
{
	return data[n][m];
}

Mat4 Mat4::operator*(const Mat4 & right) //Mat4 multiplication
{
	//if ((right._n != _m) || (error == true) || (right.error == true))
	//	return Mat4(MATRIX_ERROR);

	Mat4 result;
	//result.create(_n, right._m, false);

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			float val = 0.0f;
			for (int i3 = 0; i3 < 4; i3++)
			{
				val += data[i1][i3] * right.data[i3][i2];
			}
			result(i1, i2) = val;
		}
	}

	return result;
}

Mat4 & Mat4::operator*=(const Mat4 & right) //Mat4 multiplication
{
	//if ((right._n != _m) || (error == true) || (right.error == true))
	//	return Mat4(MATRIX_ERROR);

	Mat4 result;
	//result.create(_n, right._m, false);

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			float val = 0.0f;
			for (int i3 = 0; i3 < 4; i3++)
			{
				val += data[i1][i3] * right.data[i3][i2];
			}
			result(i1, i2) = val;
		}
	}

	*this = result;

	return *this;
}

Mat4 Mat4::operator+(const Mat4 & right) //Mat4 addiction
{
	//if ((right._n != _n) || (right._m != _m) || (error == true) || (right.error == true))
	//	return Mat4(MATRIX_ERROR);

	Mat4 result;
	//result.create(_n, _m, false);
	
	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			result(i1, i2) = data[i1][i2] + right.data[i1][i2];
		}
	}

	return result;
}

Mat4 & Mat4::operator+=(const Mat4 & right) //Mat4 addiction
{
	//if ((right._n != _n) || (right._m != _m) || (error == true) || (right.error == true))
	//	return Mat4(MATRIX_ERROR);

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			data[i1][i2] += right.data[i1][i2];
		}
	}

	return *this ;
}

Mat4 Mat4::operator-(const Mat4 & right) //Mat4 substraction
{
	//if ((right._n != _n) || (right._m != _m) || (error == true) || (right.error == true))
	//	return Mat4(MATRIX_ERROR);

	Mat4 result;
	//result.create(_n, _m, false);

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			result(i1, i2) = data[i1][i2] - right.data[i1][i2];
		}
	}

	return result;
}

Mat4 & Mat4::operator-=(const Mat4 & right) //Mat4 substraction
{
	//if ((right._n != _n) || (right._m != _m) || (error == true) || (right.error == true))
	//	return Mat4(MATRIX_ERROR);

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			data[i1][i2] -= right.data[i1][i2];
		}
	}

	return *this;
}

Mat4 & Mat4::operator=(const Mat4 arg)
{
	//create(arg._n, arg._m, false);

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			data[i1][i2] = arg.data[i1][i2];
		}
	}

	error = arg.error;

	return *this;
}

TransformationMatrix4::TransformationMatrix4()
{
	//mat.create(4, 4, true);
	mat.identity();
}

Mat4 TransformationMatrix4::scale(Vec3f v)
{
	mat.identity();

	mat(0, 0) = v.x;
	mat(1, 1) = v.y;
	mat(2, 2) = v.z;

	return mat;
}

Mat4 TransformationMatrix4::rotate(Vec3f v)
{
	float sin_x = std::sin(v.x);
	float cos_x = std::cos(v.x);
	float sin_y = std::sin(v.y);
	float cos_y = std::cos(v.y);
	float sin_z = std::sin(v.z);
	float cos_z = std::cos(v.z);

	Mat4 result;
	//result.create(4, 4, true);
	result.identity();

	result(1, 1) = cos_x;
	result(1, 2) = -sin_x;
	result(2, 1) = sin_x;
	result(2, 2) = cos_x;

	mat.identity();

	mat(0, 0) = cos_y;
	mat(0, 2) = sin_y;
	mat(2, 0) = -sin_y;
	mat(2, 2) = cos_y;

	result = result * mat;

	mat.identity();

	mat(0, 0) = cos_z;
	mat(0, 1) = -sin_z;
	mat(1, 0) = sin_z;
	mat(1, 1) = cos_z;

	result = result * mat;

	return result;
}
Mat4 TransformationMatrix4::translate(Vec3f v)
{
	mat.identity();

	mat(3, 0) = v.x;
	mat(3, 1) = v.y;
	mat(3, 2) = v.z;

	return mat;
}
#include "Matrix.h"

#include <algorithm>


m3dfw::Mat4::Mat4()
{
	identity();
}

m3dfw::Mat4::Mat4(m3dfw::MatrixInitMode init_mode)
{
	switch (init_mode)
	{
	case Zero:
		zero();
		break;

	case Identity:
		identity();
		break;
	}
}

void m3dfw::Mat4::identity()
{
	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			if (i1 == i2)
				operator()(i1, i2) = 1.0f;
			else
				operator()(i1, i2) = 0.0f;
		}
	}
}

void m3dfw::Mat4::zero()
{
	for (int i = 0; i < 16; i++)
		_data[i] = 0.0f;
}

float & m3dfw::Mat4::operator()(unsigned int m, unsigned int n)
{
	return _data[m * 4 + n];
}

float m3dfw::Mat4::operator()(unsigned int m, unsigned int n) const
{
	return _data[m * 4 + n];
}

m3dfw::Mat4 m3dfw::Mat4::operator*(const m3dfw::Mat4 & other) const
{
	Mat4 res;

	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++)
		{
			float val = 0.0f;
			for (int i3 = 0; i3 < 4; i3++)
			{
				float a = operator()(i3, i2);
				float b = other(i1, i3);

				val += a * b;;
			}
			res(i1, i2) = val;
		}
	}

	return res;
}

m3dfw::Mat4 & m3dfw::Mat4::operator*=(const m3dfw::Mat4 & other)
{
	*this = *this * other;

	return *this;
}

m3dfw::Mat4 m3dfw::Mat4::operator+(const m3dfw::Mat4 & other) const
{
	Mat4 res;

	for (int i = 0; i < 16; i++)
		res._data[i] = _data[i] + other._data[i];

	return res;
}

m3dfw::Mat4 & m3dfw::Mat4::operator+=(const m3dfw::Mat4 & other)
{
	for (int i = 0; i < 16; i++)
		_data[i] += other._data[i];

	return *this;
}

m3dfw::Mat4 m3dfw::Mat4::operator-(const m3dfw::Mat4 & other) const
{
	Mat4 res;

	for (int i = 0; i < 16; i++)
		res._data[i] = _data[i] - other._data[i];

	return res;
}

m3dfw::Mat4 & m3dfw::Mat4::operator-=(const m3dfw::Mat4 & other)
{
	for (int i = 0; i < 16; i++)
		_data[i] -= other._data[i];

	return *this;
}

const float * m3dfw::Mat4::data() const
{
	return _data;
}

void m3dfw::Mat4::translate(m3dfw::Vec3f vector)
{
	*this *= translation(vector);
}

void m3dfw::Mat4::rotate(m3dfw::Vec3f vector)
{
	*this *= rotation(vector);
}

void m3dfw::Mat4::scale(m3dfw::Vec3f vector)
{
	*this *= scaling(vector);
}

m3dfw::Mat4 m3dfw::Mat4::translation(m3dfw::Vec3f vector)
{
	Mat4 res(Identity);

	res(3, 0) = vector.x;
	res(3, 1) = vector.y;
	res(3, 2) = vector.z;

	return res;
}

m3dfw::Mat4 m3dfw::Mat4::rotation(m3dfw::Vec3f vector)
{
	Mat4 res(Identity);
	Mat4 mat(Identity);

	res(1, 1) = std::cos(-vector.x);
	res(2, 1) = -std::sin(-vector.x);
	res(1, 2) = -res(2, 1);
	res(2, 2) = res(1, 1);

	mat(0, 0) = std::cos(-vector.y);
	mat(2, 0) = std::sin(-vector.y);
	mat(0, 2) = -mat(2, 0);
	mat(2, 2) = mat(0, 0);

	res *= mat;

	mat.identity();

	mat(0, 0) = std::cos(-vector.z);
	mat(1, 0) = -std::sin(-vector.z);
	mat(0, 1) = -mat(1, 0);
	mat(1, 1) = mat(0, 0);

	res *= mat;

	return res;
}

m3dfw::Mat4 m3dfw::Mat4::scaling(m3dfw::Vec3f vector)
{
	Mat4 res(Identity);

	res(0, 0) = vector.x;
	res(1, 1) = vector.y;
	res(2, 2) = vector.z;

	return res;
}
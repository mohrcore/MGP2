#include "CommonTypes.h"

#include "Matrix.h"

#include <algorithm>


m3dfw::Vec4f::Vec4f() : x(0), y(0), z(0), w(0)
{
}

m3dfw::Vec4f::Vec4f(float v_x, float v_y, float v_z, float v_w) : x(v_x), y(v_y), z(v_z), w(v_w)
{
}

m3dfw::Vec4f m3dfw::Vec4f::operator+(const m3dfw::Vec4f & right) const
{
	return Vec4f(x + right.x, y + right.y, z + right.z, w + right.w);
}

m3dfw::Vec4f m3dfw::Vec4f::operator-(const m3dfw::Vec4f & right) const
{
	return Vec4f(x - right.x, y - right.y, z - right.z, w - right.w);
}

m3dfw::Vec4f & m3dfw::Vec4f::operator+=(const m3dfw::Vec4f & right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	w += right.w;

	return *this;
}

m3dfw::Vec4f & m3dfw::Vec4f::operator-=(const m3dfw::Vec4f & right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
	w -= right.w;

	return *this;
}

float m3dfw::Vec4f::operator*(const m3dfw::Vec4f & right) const
{
	return x * right.x + y * right.y + z * right.z + w * right.w;
}

m3dfw::Vec4f m3dfw::Vec4f::operator*(float scale) const
{
	return Vec4f(x * scale, y * scale, z * scale, w * scale);
}

m3dfw::Vec4f m3dfw::Vec4f::operator/(float div) const
{
	return Vec4f(x / div, y / div, z / div, w / div);
}

m3dfw::Vec4f & m3dfw::Vec4f::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;

	return *this;
}

m3dfw::Vec4f & m3dfw::Vec4f::operator/=(float div)
{
	x /= div;
	y /= div;
	z /= div;
	w /= div;

	return *this;
}

float m3dfw::Vec4f::length()
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}


m3dfw::Vec3f::Vec3f() : x(0), y(0), z(0)
{
}

m3dfw::Vec3f::Vec3f(float v_x, float v_y, float v_z) : x(v_x), y(v_y), z(v_z)
{
}

m3dfw::Vec3f m3dfw::Vec3f::operator+(const m3dfw::Vec3f & right) const
{
	return Vec3f(x + right.x, y + right.y, z + right.z);
}

m3dfw::Vec3f m3dfw::Vec3f::operator-(const m3dfw::Vec3f & right) const
{
	return Vec3f(x - right.x, y - right.y, z - right.z);
}

m3dfw::Vec3f & m3dfw::Vec3f::operator+=(const m3dfw::Vec3f & right)
{
	x += right.x;
	y += right.y;
	z += right.z;

	return *this;
}

m3dfw::Vec3f & m3dfw::Vec3f::operator-=(const m3dfw::Vec3f & right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;

	return *this;
}

m3dfw::Vec3f m3dfw::Vec3f::operator^(const m3dfw::Vec3f & right) const
{
	return Vec3f(y * right.z - z * right.y, z * right.x - x * right.z, x * right.y - y * right.x);
}

float m3dfw::Vec3f::operator*(const m3dfw::Vec3f & right) const
{
	return x * right.x + y * right.y + z * right.z;
}

m3dfw::Vec3f m3dfw::Vec3f::operator*(float scale) const
{
	return Vec3f(x * scale, y * scale, z * scale);
}

m3dfw::Vec3f m3dfw::Vec3f::operator/(float div) const
{
	return Vec3f(x / div, y / div, z / div);
}

m3dfw::Vec3f & m3dfw::Vec3f::operator^=(const m3dfw::Vec3f & right)
{
	x = y * right.z - z * right.y;
	y = z * right.x - x * right.z;
	z = x * right.y - y * right.x;

	return *this;
}

m3dfw::Vec3f & m3dfw::Vec3f::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;

	return *this;
}

m3dfw::Vec3f & m3dfw::Vec3f::operator/=(float div)
{
	x /= div;
	y /= div;
	z /= div;

	return *this;
}

float m3dfw::Vec3f::length()
{
	return std::sqrt(x * x + y * y + z * z);
}


m3dfw::Vec2f::Vec2f() : x(0), y(0)
{
}

m3dfw::Vec2f::Vec2f(float v_x, float v_y) : x(v_x), y(v_y)
{
}

m3dfw::Vec2f m3dfw::Vec2f::operator+(const m3dfw::Vec2f & right) const
{
	return Vec2f(x + right.x, y + right.y);
}

m3dfw::Vec2f m3dfw::Vec2f::operator-(const m3dfw::Vec2f & right) const
{
	return Vec2f(x - right.x, y - right.y);
}

float m3dfw::Vec2f::operator^(const m3dfw::Vec2f & right) const
{
	return x * right.y - y * right.x;
}

float m3dfw::Vec2f::operator*(const m3dfw::Vec2f & right) const
{
	return x * right.x + y * right.y;
}

m3dfw::Vec2f m3dfw::Vec2f::operator*(float scale) const
{
	return Vec2f(x * scale, y * scale);
}

m3dfw::Vec2f m3dfw::Vec2f::operator/(float div) const
{
	return Vec2f(x / div, y / div);
}

m3dfw::Vec2f & m3dfw::Vec2f::operator+=(const m3dfw::Vec2f & right)
{
	x += right.x;
	y += right.y;

	return *this;
}

m3dfw::Vec2f & m3dfw::Vec2f::operator-=(const m3dfw::Vec2f & right)
{
	x -= right.x;
	y -= right.y;

	return *this;
}

m3dfw::Vec2f & m3dfw::Vec2f::operator*=(float scale)
{
	x *= scale;
	y *= scale;

	return *this;
}

m3dfw::Vec2f & m3dfw::Vec2f::operator/=(float div)
{
	x /= div;
	y /= div;

	return *this;
}

float m3dfw::Vec2f::length()
{
	return std::sqrt(x * x + y * y);
}


m3dfw::Quaternion::Quaternion() : e(0.0f), i(0.0f), j(0.0f), k(0.0f)
{
}

m3dfw::Quaternion::Quaternion(float ve, float vi, float vj, float vk) : e(ve), i(vi), j(vj), k(vk)
{
}

m3dfw::Quaternion::Quaternion(m3dfw::Vec3f axis, float angle)
{
	e = std::cos(angle / 2);

	Vec3f vec_prt_res = Vec3f(i, j, k) * std::sin(angle / 2);

	i = vec_prt_res.x;
	j = vec_prt_res.y;
	k = vec_prt_res.z;
}

m3dfw::Quaternion m3dfw::Quaternion::operator+(const m3dfw::Quaternion & right) const
{
	return Quaternion(e + right.e, i + right.i, j + right.j, k + right.k);
}

m3dfw::Quaternion m3dfw::Quaternion::operator-(const m3dfw::Quaternion & right) const
{
	return Quaternion(e - right.e, i - right.i, j - right.j, k - right.k);
}

m3dfw::Quaternion m3dfw::Quaternion::operator*(const m3dfw::Quaternion & right) const
{
	Vec3f vec_prt_me(i, j, k);
	Vec3f vec_prt_right(right.i, right.j, right.k);
	Vec3f vec_prt_res(vec_prt_me ^ vec_prt_right + (vec_prt_right * e) + (vec_prt_me * right.e));

	return Quaternion(e * e - vec_prt_me * vec_prt_right, vec_prt_res.x, vec_prt_res.y, vec_prt_res.z );
}

m3dfw::Quaternion m3dfw::Quaternion::operator*(float scale) const
{
	return Quaternion(e * scale, i * scale, j * scale, k * scale);
}

m3dfw::Quaternion m3dfw::Quaternion::operator/(float div) const
{
	return Quaternion(e / div, i / div, j / div, k / div);
}

m3dfw::Quaternion & m3dfw::Quaternion::operator+=(const m3dfw::Quaternion & right)
{
	e += right.e;
	i += right.i;
	j += right.j;
	k += right.k;

	return *this;
}

m3dfw::Quaternion & m3dfw::Quaternion::operator-=(const m3dfw::Quaternion & right)
{
	e -= right.e;
	i -= right.i;
	j -= right.j;
	k -= right.k;

	return *this;
}

m3dfw::Quaternion & m3dfw::Quaternion::operator*=(const m3dfw::Quaternion & right)
{

	Vec3f vec_prt_me(i, j, k);
	Vec3f vec_prt_right(right.i, right.j, right.k);
	Vec3f vec_prt_res(vec_prt_me ^ vec_prt_right + (vec_prt_right * e) + (vec_prt_me * right.e));

	e = e * right.e - vec_prt_me * vec_prt_right;
	i = vec_prt_res.x;
	j = vec_prt_res.y;
	k = vec_prt_res.z;

	return *this;
}

m3dfw::Quaternion & m3dfw::Quaternion::operator*=(float scale)
{
	e *= scale;
	i *= scale;
	j *= scale;
	k *= scale;

	return *this;
}

m3dfw::Quaternion & m3dfw::Quaternion::operator/=(float div)
{
	e /= div;
	i /= div;
	j /= div;
	k /= div;

	return *this;
}

m3dfw::Quaternion m3dfw::Quaternion::conjugate() const
{
	return Quaternion(e, -i, -j, -k);
}

m3dfw::Quaternion m3dfw::Quaternion::inverse() const
{
	return conjugate() / norm();
}

float m3dfw::Quaternion::norm() const
{
	return std::sqrt(e * e + i * i + j * j + k * k);
}

m3dfw::Quaternion & m3dfw::Quaternion::conjugateMe()
{
	i = -i;
	j = -j;
	k = -k;

	return *this;
}

m3dfw::Quaternion & m3dfw::Quaternion::inverseMe()
{
	*this = inverse();

	return *this;
}

m3dfw::Mat4 m3dfw::Quaternion::toMatrix()
{
	Mat4 res(Zero);



	return res;
}
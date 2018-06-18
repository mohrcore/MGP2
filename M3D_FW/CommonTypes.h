#pragma once

namespace m3dfw
{
	struct Vec4f
	{
		Vec4f();
		Vec4f(float v_x, float v_y, float v_z, float v_w);

		Vec4f operator+(const Vec4f & right) const;
		Vec4f operator-(const Vec4f & right) const;
		float operator*(const Vec4f & right) const;
		Vec4f operator*(float scale) const;
		Vec4f operator/(float dic) const;

		Vec4f & operator+=(const Vec4f & right);
		Vec4f & operator-=(const Vec4f & right);
		Vec4f & operator*=(float scale);
		Vec4f & operator/=(float dic);

		float length();

		float x;
		float y;
		float z;
		float w;
	};

	struct Vec3f
	{
		Vec3f();
		Vec3f(float v_x, float v_y, float v_z);

		Vec3f operator+(const Vec3f & right) const;
		Vec3f operator-(const Vec3f & right) const;
		Vec3f operator^(const Vec3f & right) const; //Cross product
		float operator*(const Vec3f & right) const; //Dot product
		Vec3f operator*(float scale) const; //Multiplication
		Vec3f operator/(float div) const;

		Vec3f & operator+=(const Vec3f & right);
		Vec3f & operator-=(const Vec3f & right);
		Vec3f & operator^=(const Vec3f & right);
		Vec3f & operator*=(float scale);
		Vec3f & operator/=(float div);

		float length();

		float x;
		float y;
		float z;
	};

	struct Vec2f
	{
		Vec2f();
		Vec2f(float v_x, float v_y);

		Vec2f operator+(const Vec2f & right) const;
		Vec2f operator-(const Vec2f & right) const;
		float operator^(const Vec2f & right) const;
		float operator*(const Vec2f & right) const;
		Vec2f operator*(float scale) const;
		Vec2f operator/(float div) const;

		Vec2f & operator+=(const Vec2f & right);
		Vec2f & operator-=(const Vec2f & right);
		Vec2f & operator*=(float scale);
		Vec2f & operator/=(float div);

		float length();

		float x;
		float y;
	};

	class Mat4;

	struct Quaternion
	{
		Quaternion();
		Quaternion(float ve, float vi, float vj, float vk);
		Quaternion(Vec3f axis, float angle); // Axis Angle

		Quaternion operator+(const Quaternion & right) const;
		Quaternion operator-(const Quaternion & right) const;
		Quaternion operator*(const Quaternion & right) const;
		Quaternion operator*(float scale) const;
		Quaternion operator/(float div) const;

		Quaternion & operator+=(const Quaternion & right);
		Quaternion & operator-=(const Quaternion & right);
		Quaternion & operator*=(const Quaternion & right);
		Quaternion & operator*=(float scale);
		Quaternion & operator/=(float div);

		Quaternion conjugate() const;
		Quaternion inverse() const;
		float norm() const;

		m3dfw::Quaternion & conjugateMe();
		m3dfw::Quaternion & inverseMe();

		Mat4 toMatrix();

		float e;
		float i;
		float j;
		float k;
	};
}
#pragma once

#include "CommonTypes.h"

namespace m3dfw
{
	enum MatrixInitMode
	{
		Identity,
		Zero
	};

	class Mat4
	{
	public:

		Mat4();
		Mat4(MatrixInitMode int_mode);

		void identity();
		void zero();

		float & operator()(unsigned int m, unsigned int n);
		float operator()(unsigned int m, unsigned int n) const;

		Mat4 operator*(const Mat4 & other) const;
		Mat4 operator+(const Mat4 & other) const;
		Mat4 operator-(const Mat4 & other) const;

		Mat4 & operator*=(const Mat4 & other);
		Mat4 & operator+=(const Mat4 & other);
		Mat4 & operator-=(const Mat4 & other);

		void translate(Vec3f vector);
		void rotate(Vec3f vector);
		void scale(Vec3f vector);

		const float * data() const;

		static Mat4 translation(Vec3f vector);
		static Mat4 rotation(Vec3f vector);
		static Mat4 scaling(Vec3f vector);

	private:

		float _data[16];
	};
}



#include <M3DFW.h>

#include "EXPORT.h"

//Vec4f struct unwrap

m3dfw::Vec4f PTR_EXPORT(*) m3dfw__new__Vec4f()
{
	return new m3dfw::Vec4f();
}

m3dfw::Vec4f PTR_EXPORT(*) m3dfw__new__Vec4f__arg_float_float_float_float(float v_x, float v_y, float v_z, float v_w)
{
	return new m3dfw::Vec4f(v_x, v_y, v_z, v_w);
}

void EXPORT m3dfw__delete__Vec4f(m3dfw::Vec4f * ptr)
{
	delete ptr;
}

void EXPORT m3dfw__Vec4f_Add(m3dfw::Vec4f * ptr, m3dfw::Vec4f * right)
{
	*ptr += *right;
}

void EXPORT m3dfw__Vec4f_Sub(m3dfw::Vec4f * ptr, m3dfw::Vec4f * right)
{
	*ptr -= *right;
}

float EXPORT m3dfw__Vec4f_Dot(m3dfw::Vec4f * ptr, m3dfw::Vec4f * right)
{
	return *ptr * *right;
}

void EXPORT m3dfw__Vec4f_Scl(m3dfw::Vec4f * ptr, float scale)
{
	*ptr *= scale;
}

void EXPORT m3dfw__Vec4f_Div(m3dfw::Vec4f * ptr, float div)
{
	*ptr /= div;
}

float EXPORT m3dfw__Vec4f_length(m3dfw::Vec4f * ptr)
{
	return ptr->length();
}

float EXPORT m3dfw__Vec4f_Get_x(m3dfw::Vec4f * ptr)
{
	return ptr->x;
}

float EXPORT m3dfw__Vec4f_Get_y(m3dfw::Vec4f * ptr)
{
	return ptr->y;
}

float EXPORT m3dfw__Vec4f_Get_z(m3dfw::Vec4f * ptr)
{
	return ptr->z;
}

float EXPORT m3dfw__Vec4f_Get_w(m3dfw::Vec4f * ptr)
{
	return ptr->w;
}

void EXPORT m3dfw__Vec4f_Set_x(m3dfw::Vec4f * ptr, float value)
{
	ptr->x = value;
}

void EXPORT m3dfw__Vec4f_Set_y(m3dfw::Vec4f * ptr, float value)
{
	ptr->y = value;
}

void EXPORT m3dfw__Vec4f_Set_z(m3dfw::Vec4f * ptr, float value)
{
	ptr->z = value;
}

void EXPORT m3dfw__Vec4f_Set_w(m3dfw::Vec4f * ptr, float value)
{
	ptr->w = value;
}


//Vec3f struct unwrap

m3dfw::Vec3f PTR_EXPORT(*) m3dfw__new__Vec3f()
{
	return new m3dfw::Vec3f();
}

m3dfw::Vec3f PTR_EXPORT(*) m3dfw__new__Vec3f__arg_float_float_float(float v_x, float v_y, float v_z)
{
	return new m3dfw::Vec3f(v_x, v_y, v_z);
}

void m3dfw__delete__Vec3f(m3dfw::Vec3f * ptr)
{
	delete ptr;
}

void EXPORT m3dfw__Vec3f_Add(m3dfw::Vec3f * ptr,  m3dfw::Vec3f * right)
{
	ptr->operator+=(*right);
}

void EXPORT m3dfw__Vec3f_Sub(m3dfw::Vec3f * ptr, m3dfw::Vec3f * right)
{
	ptr->operator-=(*right);
}

void EXPORT m3dfw__Vec3f_Cross(m3dfw::Vec3f * ptr, m3dfw::Vec3f * right)
{
	ptr->operator^=(*right);
}

float EXPORT m3dfw__Vec3f_Dot(m3dfw::Vec3f * ptr, m3dfw::Vec3f * right)
{
	return ptr->operator*(*right);
}

void EXPORT m3dfw__Vec3f_Scl(m3dfw::Vec3f * ptr, float scale)
{
	ptr->operator*=(scale);
}

void EXPORT m3dfw__Vec3f_Div(m3dfw::Vec3f * ptr, float div)
{
	ptr->operator/=(div);
}

float EXPORT m3dfw__Vec3f_length(m3dfw::Vec3f * ptr)
{
	return ptr->length();
}

float EXPORT m3dfw__Vec3f_Get_x(m3dfw::Vec3f * ptr)
{
	return ptr->x;
}

float EXPORT m3dfw__Vec3f_Get_y(m3dfw::Vec3f * ptr)
{
	return ptr->y;
}

float EXPORT m3dfw__Vec3f_Get_z(m3dfw::Vec3f * ptr)
{
	return ptr->z;
}

void EXPORT m3dfw__Vec3f_Set_x(m3dfw::Vec3f * ptr, float value)
{
	ptr->x = value;
}

void EXPORT m3dfw__Vec3f_Set_y(m3dfw::Vec3f * ptr, float value)
{
	ptr->y = value;
}

void EXPORT m3dfw__Vec3f_Set_z(m3dfw::Vec3f * ptr, float value)
{
	ptr->z = value;
}

//Vec2f struct unwrap

m3dfw::Vec2f PTR_EXPORT(*) m3dfw__new__Vec2f()
{
	return new m3dfw::Vec2f();
}

m3dfw::Vec2f PTR_EXPORT(*) m3dfw__new__Vec2f__arg_float_float(float v_x, float v_y)
{
	return new m3dfw::Vec2f(v_x, v_y);
}

void m3dfw__delete__Vec2f(m3dfw::Vec2f * ptr)
{
	delete ptr;
}

void EXPORT m3dfw__Vec2f_Add(m3dfw::Vec2f * ptr, m3dfw::Vec2f * right)
{
	ptr->operator+=(*right);
}

void EXPORT m3dfw__Vec2f_Sub(m3dfw::Vec2f * ptr, m3dfw::Vec2f * right)
{
	ptr->operator-=(*right);
}


void EXPORT m3dfw__Vec2f_Scl(m3dfw::Vec2f * ptr, float scale)
{
	ptr->operator*=(scale);
}

void EXPORT m3dfw__Vec2f_Div(m3dfw::Vec2f * ptr, float div)
{
	ptr->operator/=(div);
}

float EXPORT m3dfw__Vec2f_Dot(m3dfw::Vec2f * ptr, m3dfw::Vec2f * right)
{
	return ptr->operator*(*right);
}

float EXPORT m3dfw__Vec2f_length(m3dfw::Vec2f * ptr)
{
	return ptr->length();
}

float EXPORT m3dfw__Vec2f_Get_x(m3dfw::Vec2f * ptr)
{
	return ptr->x;
}

float EXPORT m3dfw__Vec2f_Get_y(m3dfw::Vec2f * ptr)
{
	return ptr->y;
}

void EXPORT m3dfw__Vec2f_Set_x(m3dfw::Vec2f * ptr, float value)
{
	ptr->x = value;
}

void EXPORT m3dfw__Vec2f_Set_y(m3dfw::Vec2f * ptr, float value)
{
	ptr->y = value;
}

//Quaternion struct unwrap

m3dfw::Quaternion PTR_EXPORT(*) m3dfw__new__Quaternion()
{
	return new m3dfw::Quaternion();
}

m3dfw::Quaternion PTR_EXPORT(*) m3dfw__new__Quaternion__arg_float_float_float_float(float ve, float vi, float vj, float vk)
{
	return new m3dfw::Quaternion(ve, vi, vj, vk);
}

void m3dfw__delete__Quaternion(m3dfw::Quaternion * ptr)
{
	delete ptr;
}

void EXPORT m3dfw__Quaternion_toMatrix(m3dfw::Quaternion * ptr, m3dfw::Mat4 * target)
{
	*target = ptr->toMatrix();
}

float EXPORT m3dfw__Quaternion_Get_e(m3dfw::Quaternion * ptr)
{
	return ptr->e;
}

float EXPORT m3dfw__Quaternion_Get_i(m3dfw::Quaternion * ptr)
{
	return ptr->i;
}

float EXPORT m3dfw__Quaternion_Get_j(m3dfw::Quaternion * ptr)
{
	return ptr->j;
}

float EXPORT m3dfw__Quaternion_Get_k(m3dfw::Quaternion * ptr)
{
	return ptr->k;
}

void EXPORT m3dfw__Quaternion_Set_e(m3dfw::Quaternion * ptr, float value)
{
	ptr->e = value;
}

void EXPORT m3dfw__Quaternion_Set_i(m3dfw::Quaternion * ptr, float value)
{
	ptr->i = value;
}

void EXPORT m3dfw__Quaternion_Set_j(m3dfw::Quaternion * ptr, float value)
{
	ptr->j = value;
}

void EXPORT m3dfw__Quaternion_Set_k(m3dfw::Quaternion * ptr, float value)
{
	ptr->k = value;
}
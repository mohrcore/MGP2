#include <SDL.h>
#include <GL/glew.h>

#include "Util.h"
#include "Clock.h"

#include "Camera.h"



Camera::Camera(BinaryInput & bi) : _bi(bi), _m_translation(Vec3f(0.0f, 0.0f, 0.0f))
{
}


Camera::~Camera()
{
}

void Camera::move(Vec3f vector)
{
	_translation -= vector;
}

void Camera::rotate(Vec3f vector)
{
	_angle -= vector;
}

void Camera::setPosition(Vec3f position)
{
	_translation = Vec3f(-position.x, -position.y, -position.z);
}

void Camera::setAngle(Vec3f angle)
{
	_angle = Vec3f(-angle.x, -angle.y, -angle.z);
}

void Camera::setSpeed(float speed)
{
	_speed = speed;
}

Vec3f Camera::getPosition()
{
	return Vec3f(-_translation.x - _m_translation.x, -_translation.y - _m_translation.y, -_translation.z - _m_translation.z);
}

Vec3f Camera::getAngle()
{
	return Vec3f(-_angle.x, -_angle.y, -_angle.z);
}

Mat4 Camera::viewMatrix()
{
	Mat4 result;
	result.identity();

	result *= tm.translate(_translation - _m_translation);
	return result * tm.translate(_angle);

}

void Camera::update()
{
	if (_prev_input_state != _bi.getAllStates())
	{
		_translation -= _m_translation;
		_m_translation = Vec3f(0.0f, 0.0f, 0.0f);
		_moveclock.restart();
	}

	_prev_input_state = _bi.getAllStates();

	float translation_factor_x = 0.0f;
	float translation_factor_y = 0.0f;
	float translation_factor_z = 0.0f;

	if (_bi.getInputState(IS_KEY_W))
		translation_factor_z = -_speed;
	if (_bi.getInputState(IS_KEY_A))
		translation_factor_x = -_speed;
	if (_bi.getInputState(IS_KEY_S))
		translation_factor_z = _speed;
	if (_bi.getInputState(IS_KEY_D))
		translation_factor_x = _speed;

	_m_translation = Vec3f(translation_factor_x * _moveclock.getTime(), translation_factor_y * _moveclock.getTime(), translation_factor_z * _moveclock.getTime());
}
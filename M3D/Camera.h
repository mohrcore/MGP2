#pragma once

#include <GL/glew.h>

#include "Util.h"
#include "Clock.h"
#include "Matrix.h"

class Camera
{
public:

	Camera(BinaryInput & bi);
	~Camera();

	void move(Vec3f vector);
	void rotate(Vec3f angle);
	void setPosition(Vec3f position);
	void setAngle(Vec3f angle);
	void setSpeed(float speed);

	void update();

	Vec3f getPosition();
	Vec3f getAngle();

	Mat4 viewMatrix();

private:

	Vec3f _translation;
	Vec3f _angle;

	Vec3f _m_translation; //translation to apply while moving

	TransformationMatrix4 tm;

	BinaryInput & _bi;

	uint64_t _prev_input_state;

	Clock _moveclock;

	float _speed;
};


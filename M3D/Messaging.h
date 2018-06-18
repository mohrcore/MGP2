#pragma once

#include <vector>

enum __F_M_data_type
{
	M3D_CHAR,
	M3D_UNSIGNED_CHAR,
	M3D_INT,
	M3D_UNSIGNED_INT,
	M3D_FLOAT,
	M3D_UNSIGNED_FLOAT,
	M3D_VERTEX,
	M3D_COLOR,
	M3D_RECT2D,
	M3D_VEC2F,
	M3D_VEC3F
};

struct F_Message
{
	F_Message(long msg_content, void * msg_data);

	long content;
	long target_system;
	__F_M_data_type data_type;
	void * data;
};

class F_MessageBus
{
	std::vector<F_Message> messages;

};

class F_MessageSender
{
public:

	F_MessageSender();
	~F_MessageSender();

	void ms_SendMessage(long message, void * data);
};


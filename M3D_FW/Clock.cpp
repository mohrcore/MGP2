#include "Clock.h"



m3dfw::Clock::Clock()
{
	restart();
}


m3dfw::Clock::~Clock()
{
}


double m3dfw::Clock::getTime()
{
	return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - _start_time).count();
}

void m3dfw::Clock::restart()
{
	_start_time = std::chrono::steady_clock::now();
}
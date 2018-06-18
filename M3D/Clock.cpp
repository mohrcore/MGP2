#include <ctime>

#include "Clock.h"



Clock::Clock() : start(std::clock())
{
}


double Clock::getTime()
{
	return (std::clock() - start) / (double)CLOCKS_PER_SEC;
}

void Clock::restart()
{
	start = std::clock();
}
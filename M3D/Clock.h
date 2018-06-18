#pragma once

#include <ctime>

struct Clock
{
public:

	Clock();

	double getTime();
	void restart();

private:

	std::clock_t start;
};


#pragma once

#include <chrono>

namespace m3dfw
{
	class Clock
	{
	public:

		Clock();
		~Clock();

		double getTime();

		void restart();

	private:

		std::chrono::steady_clock _clock;
		std::chrono::steady_clock::time_point _start_time;
	};
}


#pragma once

#include <list>

#include "Clock.h"
#include "System.h"
#include "TaskManager.h"

namespace m3dfw
{
	class SchedulerLS //Lock step mode Sscheduler
	{
	public:

		SchedulerLS(TaskManager * tm, double freq);
		~SchedulerLS();

		void addTask(void (*task)());

		void execute();

	private:

		double _master_period;

		Clock _master_clock;

		std::list<void(*)()> _task_list;

		TaskManager * _tm;

		System * * _sys;
	};
}


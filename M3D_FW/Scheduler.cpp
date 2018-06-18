#include "Scheduler.h"



m3dfw::SchedulerLS::SchedulerLS(TaskManager * tm, double freq) : _master_period(1 / freq), _tm(tm)
{
}


m3dfw::SchedulerLS::~SchedulerLS()
{
}


void m3dfw::SchedulerLS::addTask(void (*task)())
{
	_task_list.push_back(task);
}

void m3dfw::SchedulerLS::execute()
{
	if (_master_clock.getTime() >= _master_period)
	{
		for (std::list<void(*)()>::iterator it = _task_list.begin(); it != _task_list.end(); it++)
		{
			_tm->assignTask(*it);
		}
	}
}
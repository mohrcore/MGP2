#include "System.h"


m3dfw::System::System()
{
}


m3dfw::System::~System()
{
}


m3dfw::SystemFct m3dfw::System::pollTask()
{
	SystemFct ptr = _task_pool.front();
	_task_pool.pop();
	return ptr;
}

void m3dfw::System::addTask(m3dfw::SystemFct task)
{
	_task_pool.push(task);
}

m3dfw::SysArg::SysArg(std::atomic_int & t_prog_ref) : task_progress(t_prog_ref)
{
}
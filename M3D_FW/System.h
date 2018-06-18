#pragma once

#include <queue>
#include <string>
#include <iostream>
#include <atomic>

#include "Messages.h"

#define WAIT_FOR_TASK_COMPLETION nullptr


//		-----{ About systems }----------------------------------------------------------------------------------------------------------------------------------
//		System provides base class for every system (eg. graphisc, physics, AI), giving them common functionality for managing execution, and tasks queueing
//		System execution can be triggered by calling System::execute method
//		During the execution system will store it's tasks to the _task_pool queue.
//		TaskManager2 will decide which tasks pools from which systems are ought to be polled at the moment and will execute tasks on those queues
//		--------------------------------------------------------------------------------------------------------------------------------------------------------


#define CAST_DSYS_MEMBER(X) static_cast<m3dfw::SystemFct>(&X)


namespace m3dfw
{
	class System;

	struct SysArg;

	typedef void(System::*SystemFct)(SysArg const *);

	class System
	{
	public:

		System();
		~System();

		virtual void execute() =0; //Initializes system execution

		SystemFct pollTask();

	protected:

		void addTask(SystemFct task);

	private:

		std::queue<SystemFct> _task_pool; //Will store pointers to member functions of derieved classes (using static_cast)
	};

	struct SysArg
	{
		friend class System;

	public:

		SysArg(std::atomic_int & t_prog_ref);


	private:

		std::atomic_int & task_progress;
	};
}
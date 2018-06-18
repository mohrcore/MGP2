#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

//#include "cvmarkersobj.h"

//Task manager is used to assign task to avaible threads

namespace m3dfw
{
	class TaskManager
	{
	public:

		TaskManager(unsigned int threads_no);
		~TaskManager();

		//bool isFree(); //Returns true if there are any avaible threads
		void assignTask(void(*task)()); //Take pointer to a void function and executes the function on avaible thread
		void waitTillFinished(); //Waits until the all tasks are finished

	private:

		void run();

		std::thread * _threads;
		//bool * _is_thread_free;

		std::queue<void (*)()> _task_queue;

		unsigned int _threads_no;
		unsigned int _active_threads;

		std::atomic_int _to_do_no; //Number of tasks not done yet.

		bool _quit_threads;

		std::mutex _queue_mutex;
		std::condition_variable _thread_avaible;
		std::condition_variable _task_added;
	};
}



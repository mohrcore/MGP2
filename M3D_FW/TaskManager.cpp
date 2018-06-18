#include "TaskManager.h"



m3dfw::TaskManager::TaskManager(unsigned int threads_no) : _threads_no(threads_no), _active_threads(0), _to_do_no(0)
{
	_threads = new std::thread[_threads_no];
	//_is_thread_free = new bool[_threads_no];
	//for (int i = 0; i < _threads_no; i++)
	//	_is_thread_free[i] = true;

	for (int i = 0; i < _threads_no; i++)
		_threads[i] = std::thread(&TaskManager::run, this);
}


m3dfw::TaskManager::~TaskManager()
{
	_quit_threads = true; //Notify all threads that they should stop pooling for new tasks

	_task_added.notify_all();

	for (int i = 0; i < _threads_no; i++) //Wait for threads to synchronize
		_threads[i].join();

	delete[] _threads;
	//delete _is_thread_free;
}

void m3dfw::TaskManager::assignTask(void(*task)())
{
	bool done = false;

	//while (!done)
	//{
	//	std::unique_lock<std::mutex> lock(_queue_mutex);
	//	if (_task_queue.size() < _threads_no)
	//	{
	//		_task_queue.push(task);

	//		_task_added.notify_all();

	//		done = true;
	//	}
	//	else
	//	{
	//		_thread_avaible.wait(lock); //Wait until a thread is avaible to avoid queueing too many instruction
	//		_task_added.notify_all();
	//	}
	//}

	std::unique_lock<std::mutex> lock(_queue_mutex);

	_task_queue.push(task);

	_to_do_no++;

	_task_added.notify_all();
}

void m3dfw::TaskManager::run()
{
	while (!_quit_threads)
	{
		std::unique_lock<std::mutex> lock(_queue_mutex);
		

		if (!_task_queue.empty()) //Suprious wakeup check
		{
			void(*task)() = _task_queue.front(); //What if there are no tasks on the queue?
			_task_queue.pop();

			lock.unlock();

			task();

			_to_do_no--;

			_thread_avaible.notify_all(); //Notify, that the thread has finished it's task
		}
		else
		{
			_task_added.wait(lock);
		}
	}
}

void m3dfw::TaskManager::waitTillFinished()
{
	bool done = false;

	while (!done)
	{
		std::unique_lock<std::mutex> lock(_queue_mutex);

		if (_to_do_no == 0)
			done = true;
		else
			_thread_avaible.wait(lock);
	}
}
#pragma once

//#include <map>
//#include <list>
//#include <queue>
//#include <mutex>
//
//#include "Message.h"
//#include "Messenger.h"
//
//namespace m3dfw
//{
//
//	class ChangeController
//	{
//	public:
//
//		ChangeController();
//		~ChangeController();
//
//		//void receive(Message msg, void * sender);
//		//void deliver();
//
//	private:
//
//		std::map<void *, void *> _receivers;
//		std::queue<Message> _msg_queue;
//
//		std::mutex _msg_queue_mutex; //This method should be performed only once every synchronisation cycle, since it locks _msg_queue causing any threads that are willing to send a message to wait.
//		std::condition_variable _msg_push;
//	};
//
//}
//

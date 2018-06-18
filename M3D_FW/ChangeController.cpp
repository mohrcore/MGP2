#include "ChangeController.h"



//m3dfw::ChangeController::ChangeController()
//{
//}
//
//m3dfw::ChangeController::~ChangeController()
//{
//}
//
//
////void m3dfw::ChangeController::receive(Message msg, void * sender) //receive a message
////{
////	std::lock_guard<std::mutex> locker(_msg_queue_mutex); //Locking the thread
////
////	_msg_queue.push(msg);
////}
////
////void m3dfw::ChangeController::deliver()
////{
////	std::lock_guard<std::mutex> locker(_msg_queue_mutex); //Locking the thread
////	while (!_msg_queue.empty())
////	{
////		((Messenger *)(_msg_queue.front().sender))->receiveMessage(_msg_queue.front()); //Send a message to a messenger object
////		_msg_queue.pop();
////	}
////}
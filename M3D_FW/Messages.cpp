#include "Messages.h"


void m3dfw::MessageManager::sendMessages()
{
	while (!_message_queue.empty())
	{
		MsgType msg_type = _message_queue.front()->type;
		for (std::list<m3dfw::MessageReceiver *>::iterator it = _receivers[msg_type].begin(); it != _receivers[msg_type].end(); it++)
		{
			(*it)->processMessage(*_message_queue.front());
		}
		
		delete _message_queue.front();
		_message_queue.pop();
	}
}

void m3dfw::MessageManager::subscribe(m3dfw::MessageReceiver * receiver, MsgType msg_type)
{
	_receivers[msg_type].push_back(receiver);
}

void m3dfw::MessageManager::unsubscribe(m3dfw::MessageReceiver * receiver, MsgType msg_type)
{
	std::list<m3dfw::MessageReceiver *>::iterator it = _receivers[msg_type].begin();
	while (*it != receiver)
		it++;

	_receivers[msg_type].erase(it);
}

m3dfw::MessageReceiver::MessageReceiver(m3dfw::MessageManager & mm) : _mm(mm)
{
}

m3dfw::MessageReceiver::~MessageReceiver()
{
	for(std::list<MsgType>::iterator it = _subscribed_types.begin(); it != _subscribed_types.end(); it++)
	{
		unsubscribe(*it);
	}
}

void m3dfw::MessageReceiver::subscribe(MsgType type)
{
	_mm.subscribe(this, type);
	_subscribed_types.push_back(type);
}

void m3dfw::MessageReceiver::unsubscribe(MsgType type)
{
	_mm.unsubscribe(this, type);
}

m3dfw::MessageSender::MessageSender(m3dfw::MessageManager & mm) : _mm(mm)
{
}


void m3dfw::MessageReceiver::processMessage(m3dfw::MessageBase & msg)
{
}
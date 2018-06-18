#pragma once


//		-----[Message System]-------------------------------------------------------------------------------------------------
//		Message system using templates and polymorphism, designed by Krzysztof Boroñski
//		
//		This system allows easy communication between objects without loose-coupling. Every object that inherits from
//		m3dfw::MessageSender can send a message of certain category ("type"), that can contain data of any type.
//		Messages of certain category should contain the same type of data in order to avoid incorrect casting.
//		Objects that inherit from m3dfw::MessageReceiver can register to receive messages of certain category ("type")
//		When a message of subscribed type is being sent, MessageManager calls
//		virtual void m3dfw::MessageReceiver::processMessage(m3df::MessageBase & msg). This method is empty by default and is
//		meant to be overridden by user (this can be also done by using simple M3D_PROCESS_MSG(NAME) macro). The user can
//		decide what to do when the message is received.
//		m3dfw::MessageManager is used to manage messages and send them to receivers when
//		void m3dfw::MessageManager::sendMessages is called.
//		
//		The system is currently not thread-safe.
//		----------------------------------------------------------------------------------------------------------------------

#include <map>
#include <list>
#include <queue>
#include <mutex>

#include "MessageTypes.h"


#define M3D_PROCESS_MSG(NAME) virtual void processMessage(m3dfw::MessageBase & NAME) //Macro used to easly define how to prosecc messages


namespace m3dfw
{
	typedef unsigned short MsgType;

	class MessageSender;
	class MessageReceiver;

	class MessageBase
	{
	public:

		inline MessageBase(MessageSender * m_sender, MsgType m_type);
		inline virtual ~MessageBase();

		template <typename T> T getData();

		MessageSender * sender;
		short type;
	};

	template <typename C>
	class Message
		: public MessageBase
	{
	public:

		Message(MessageSender * msg_sender, MsgType msg_type, const C & msg_data);
		virtual ~Message();

		C data;
	};

	class MessageManager
	{
	public:

		template <typename T> void postMessage(MessageSender * msg_sender, MsgType msg_type, const T & msg_data);
		void sendMessages();
		void subscribe(MessageReceiver * receiver, MsgType msg_type);
		void unsubscribe(MessageReceiver * receiver, MsgType msg_type);

	private:

		std::map<MsgType, std::list<MessageReceiver *>> _receivers;

		std::queue<MessageBase *> _message_queue;

		std::mutex _message_queue_mutex;
	};

	class MessageSender
	{
	public:

		MessageSender(MessageManager & mm);

		template <typename T> void sendMessage(MsgType msg_type, const T & msg_data);

	private:

		MessageManager & _mm;
	};

	class MessageReceiver
	{
	public:

		MessageReceiver(MessageManager & mm);
		virtual ~MessageReceiver();

		virtual void processMessage(MessageBase & msg);

		void subscribe(MsgType type);
		void unsubscribe(MsgType type);

	private:

		MessageManager & _mm;

		std::list<MsgType> _subscribed_types;
	};
}


// TEMPLATE IMPLEMENTATIONS ----------------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
T m3dfw::MessageBase::getData()
{
	return dynamic_cast<m3dfw::Message<T> *>(this)->data;
}

template <typename C>
m3dfw::Message<C>::Message(m3dfw::MessageSender * msg_sender, MsgType msg_type, const C & msg_data) : MessageBase(msg_sender, msg_type), data(msg_data)
{
}

template <typename C>
m3dfw::Message<C>::~Message()
{
}

template <typename T>
void m3dfw::MessageManager::postMessage(MessageSender * msg_sender, MsgType msg_type, const T & msg_data)
{
	std::lock_guard<std::mutex> queue_lock(_message_queue_mutex);
	_message_queue.push(new Message<T>(msg_sender, msg_type, msg_data));
}

template <typename T>
void m3dfw::MessageSender::sendMessage(MsgType msg_type, const T & msg_data)
{
	_mm.postMessage(this, msg_type, msg_data);
}


m3dfw::MessageBase::MessageBase(MessageSender * m_sender, MsgType m_type) : sender(m_sender), type(m_type)
{
}

m3dfw::MessageBase::~MessageBase()
{
}
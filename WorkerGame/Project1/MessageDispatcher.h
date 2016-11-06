#pragma once
#include <set>
#include "Message.h"
#include <thread>
#define Dispatcher MessageDispatcher::Instance();
class MessageDispatcher
{
	std::set<Message> pqueue_messages;
public:
	MessageDispatcher();
	~MessageDispatcher();
	void send(Message m);
	void dispatch(Message m);
	static MessageDispatcher* Instance()
	{
		static MessageDispatcher dis;
		return &dis;
	}
};


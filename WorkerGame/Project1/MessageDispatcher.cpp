#include "MessageDispatcher.h"
#include "EntityManager.h"


MessageDispatcher::MessageDispatcher()
{
}


MessageDispatcher::~MessageDispatcher()
{
}

void MessageDispatcher::dispatch(Message m)
{
	BaseGameEntity* reciever = EntityMgr->getEntityById(m.receiver);
	reciever->HandleMessage(m);
}

void MessageDispatcher::send(Message m)
{
	
	if(m.delay == 0)
	{
		dispatch(m);
	}
	else 
	{
		pqueue_messages.insert(m);
	}
}

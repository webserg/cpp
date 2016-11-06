#ifndef BASEGAMEENTITY_H
#define BASEGAMEENTITY_H
#include "Message.h"

class Message;

class BaseGameEntity
{
private:
	int id;
public:
	BaseGameEntity(int id) : id{id}
	{
	}
	virtual ~BaseGameEntity() {}
	virtual void Update() = 0;
	virtual void HandleMessage(const Message& m) = 0;
	int ID() const { return id; }
};
#endif
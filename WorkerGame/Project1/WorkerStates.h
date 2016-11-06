#ifndef WORKERSTATES_H
#define WORKERSTATES_H
#pragma once
#include "StateMachine.h"
#include "Worker.h"
class Worker;
class GoHomeAndRestState : public State<Worker>
{
	GoHomeAndRestState() {};
	GoHomeAndRestState(const GoHomeAndRestState& c);//copy constuctor
	GoHomeAndRestState& operator=(const GoHomeAndRestState&);// copy assignment

public:
	
	static GoHomeAndRestState* Instance();

	virtual void Enter(Worker* w) override;

	virtual void Execute(Worker* w);

	virtual void Exit(Worker* w);

	virtual bool onMessage(Worker*, const Message&) override;
};

class EnterWorkAndMakeMoney : public State<Worker>
{
	EnterWorkAndMakeMoney() {};
	EnterWorkAndMakeMoney(const EnterWorkAndMakeMoney& c);//copy constuctor
	EnterWorkAndMakeMoney& operator=(const EnterWorkAndMakeMoney&);// copy assignment

public:

	static EnterWorkAndMakeMoney* Instance();

	virtual void Enter(Worker* w);

	virtual void Execute(Worker* w);

	virtual void Exit(Worker* w) override;

	virtual bool onMessage(Worker*, const Message&) override;
};
#endif


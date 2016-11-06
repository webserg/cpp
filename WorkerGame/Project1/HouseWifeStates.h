#ifndef HOUSEWIFESTATES_H
#define HOUSEWIFESTATES_H
#include "HouseWife.h"
#include "State.h"
class HouseWife;
class GoAndCookState : public State<HouseWife>
{
	GoAndCookState() {};
	GoAndCookState(const GoAndCookState& c);//copy constuctor
	GoAndCookState& operator=(const GoAndCookState&);// copy assignment

public:

	static GoAndCookState* Instance();

	virtual void Enter(HouseWife* w) override;

	virtual void Execute(HouseWife* w) override;

	virtual void Exit(HouseWife* w) override;

	virtual bool onMessage(HouseWife*, const Message&);
};
class RestAndWaitState : public State<HouseWife>
{
	RestAndWaitState() {};
	RestAndWaitState(const RestAndWaitState& c);//copy constuctor
	RestAndWaitState& operator=(const RestAndWaitState&);// copy assignment

public:

	static RestAndWaitState* Instance();

	virtual void Enter(HouseWife* w) override;

	virtual void Execute(HouseWife* w) override;

	virtual void Exit(HouseWife* w) override;

	virtual bool onMessage(HouseWife*, const Message&);
};
#endif



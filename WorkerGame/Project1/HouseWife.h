#ifndef HOUSEWIFE_H
#define HOUSEWIFE_H
#include "main.h"
class Lunch {
	Lunch() {};
	Lunch(const Lunch& c);//copy constuctor
	Lunch& operator=(const Lunch&);// copy assignment
	int level;
public:

	static Lunch* Instance() {
		static Lunch instance;
		return &instance;
	}
	void increase() {
		level++;
	}
	void decrease() {
		level -= 10;
	}
	bool isReady() {
		return level > 10;
	}

};
class HouseWife: public BaseGameEntity
{
	StateMachine<HouseWife>* stateMachine;
public:
	HouseWife(int id);
	~HouseWife() {
		delete stateMachine;
	};
	void Update() override;
	void HandleMessage(const Message& m) override;
	void HouseWife::ChangeState(State<HouseWife>* pNewState) { stateMachine->ChangeState(pNewState); }
	StateMachine<HouseWife>* GetFSM()const { return stateMachine; }
};
#endif

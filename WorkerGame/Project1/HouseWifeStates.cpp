#include "HouseWifeStates.h"
#include "main.h"
#include "MessageDispatcher.h"
#include "Message.h"

class GoAndCookState* GoAndCookState::Instance() {
	static GoAndCookState instance;
	return &instance;
}

void GoAndCookState::Enter(HouseWife* w) {
	cout << "enter go and cook state" << "\n";
}

void GoAndCookState::Execute(HouseWife* w) {
	Lunch *lunch = Lunch::Instance();
	if (lunch->isReady()) {
		w->ChangeState(RestAndWaitState::Instance());
		Message m{ 2,1, message_type::Msg_StewReady ,0.0 };
		MessageDispatcher::Instance()->send(m);

	}
	else {
		lunch->increase();	
	}
}

void GoAndCookState::Exit(HouseWife* w) {}

bool GoAndCookState::onMessage(HouseWife* wife_entity, const Message& message)
{
	switch(message.msg)
	{
	case Msg_HiHoneyImHome:
		
		return true;
	}
	return false;
}

class RestAndWaitState* RestAndWaitState::Instance() {
	static RestAndWaitState instance;
	return &instance;
}

void RestAndWaitState::Enter(HouseWife* w) {

}

void RestAndWaitState::Execute(HouseWife* w) {
	Lunch *lunch = Lunch::Instance();
	if (lunch->isReady()) {
		cout << "just rest" << "\n";
	}
	else {
		w->ChangeState(GoAndCookState::Instance());
	}
}

bool RestAndWaitState::onMessage(HouseWife* wife_entity, const Message& message)
{
	switch (message.msg)
	{
	case Msg_HiHoneyImHome:
		wife_entity->ChangeState(GoAndCookState::Instance());
		return true;
	}
	return false;
}

void RestAndWaitState::Exit(HouseWife* w) {}



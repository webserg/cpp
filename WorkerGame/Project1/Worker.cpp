#include "Worker.h"

Worker::Worker(int id) : location{home}, BaseGameEntity(id) {
	stateMachine = new StateMachine<Worker>(this);
	stateMachine->SetCurrentState(GoHomeAndRestState::Instance());
}

void Worker::Update() {
	stateMachine->Update();
}

void Worker::HandleMessage(const Message& m)
{
	stateMachine->HandleMessage(m);
}


#include "main.h"
#include "Worker.h"
#include "HouseWife.h"
#include "EntityManager.h"
int main() {
	
	Worker worker1(1);
	HouseWife houseWife(2);
	EntityMgr->addEntity(&worker1);
	EntityMgr->addEntity(&houseWife);
	for (auto i = 0; i < 30; ++i)
	{
		worker1.Update();
		houseWife.Update();
		Sleep(500);
	}

	keep_window_open();
	return 0;
}
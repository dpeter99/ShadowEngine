#include "Debug.h"
#include <iostream>
#include "ShadowEvents/ShadowEventManager.h"


void Debug::Init()
{
	ShadowEventManager::AddNewEventListener(this);
}

void Debug::OnEvent(ShadowEvent& e)
{
	std::cout << e.ToString() << std::endl;
}

Debug::Debug()
{
}


Debug::~Debug()
{
}

#include <Core/Core.h>

#include "TestGame.h"

ShadowEngine::IGame* entryPoint()
{
	return new TestGame();
}

ShadowEngine::SetupFunction _setupFunc = entryPoint;
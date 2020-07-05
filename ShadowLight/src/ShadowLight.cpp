#include "ShadowLight.h"

#include "Log.h"

ShadowEngine::IGame* entryPoint()
{
	return new ShadowLight();
}

ShadowEngine::SetupFunction _setupFunc = entryPoint;

void ShadowLight::Init()
{
	SH_INFO("Game Init");
}

void ShadowLight::Start()
{
}

void ShadowLight::Stop()
{
}

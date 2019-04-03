#include "ShadowApplication.h"
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowMap/ShadowWorld.h"
#include "ShadowAsset/AssetManager.h"
#include "ShadowMap/ShadowMapRenderer.h"


ShadowApplication::ShadowApplication()
{
		
}


ShadowApplication::~ShadowApplication()
{
}

void ShadowApplication::Start()
{
	ShadowWorld* w = AssetManager::GetAsset<ShadowWorld>("Resources/Worlds/Default/overworld.txt");
	w->SetActiveMap("default");
	w->Update(ShadowMath::Vector2float(0, 0));
	//ShadowMapRenderer::RenderMap(*map);

	while(running)
	{
		
	}
}

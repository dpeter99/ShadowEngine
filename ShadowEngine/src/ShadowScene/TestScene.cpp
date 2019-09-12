#include "shpch.h"
#include "TestScene.h"
#include <ShadowEntity\Entities\Camera.h>

void TestScene::Init()
{
	Camera* c = AddNewInstance<Camera>();
	c->SetupOrthographic();


	ShadowScene::Init();
}

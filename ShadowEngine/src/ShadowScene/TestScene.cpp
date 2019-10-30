#include "shpch.h"
#include "TestScene.h"
#include <ShadowEntity\Entities\Camera.h>

void TestScene::Init()
{
	Camera* c = AddNewInstance<Camera>();
	c->SetupOrthographic();
	c->transform.SetPosition({ 0,0.3f,0.0f });

	ShadowScene::Init();
}

#include "shpch.h"
#include "TestScene.h"
#include <ShadowEntity\Entities\Camera.h>

void TestScene::Init()
{
	AddNewInstance<Camera>(Camera::CameraType::Orthographic);
}

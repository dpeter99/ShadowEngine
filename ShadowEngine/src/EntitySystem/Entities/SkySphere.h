#pragma once
#include "EntitySystem/Entity.h"
#include "MeshRenderer.h"


class SkySphere: public ShadowEngine::EntitySystem::Entity
{
	SHObject_Base(SkySphere)
private:
	ShadowEngine::EntitySystem::rtm_ptr<MeshRenderer> renderer;
public:
	void Init() override;
	
};


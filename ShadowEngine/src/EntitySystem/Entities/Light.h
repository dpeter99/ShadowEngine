#pragma once

#include "EntitySystem/SceneEntity.h"
#include <Inspector\EntityInspector.h>
#include <EntitySystem\Entities\Internal\Inspectors\DefaultInspectors.h>

class Light : public ShadowEngine::EntitySystem::SceneEntity
{
	SHObject_Base(Light)
	Entity_Base(Light, SceneEntity)

public:
	void Render() override;
};

class LightInspector : public ShadowEngine::Debug::EntityInspector {

public:
	void Draw(ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::Entity>& obj) override {
		//ShadowEngine::EntitySystem::rtm_ptr<Camera> cam = obj;
		DrawTransformInspector((ShadowEngine::EntitySystem::rtm_ptr<ShadowEngine::EntitySystem::SceneEntity>)obj);
	}
};
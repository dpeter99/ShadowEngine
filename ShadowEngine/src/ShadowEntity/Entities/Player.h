#pragma once

#include "../EntityRegistry.h"
#include "ShadowEntity/SceneEntity.h"


class Player : public ShadowEngine::ShadowEntity::SceneEntity
{
	SHObject_Base(Player)
		Entity_Base(Player, SceneEntity)

public:
	static std::string id;



	void Render() override;

	// Inherited via SceneEntity
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void LateRender() override;
	virtual ShadowEngine::ShadowEntity::EntityFlags GetFlags() override;
};

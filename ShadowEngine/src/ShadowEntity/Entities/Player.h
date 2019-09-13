//
// Created by dpete on 2/17/2019.
//

#ifndef SHADOWENGINE_PLAYER_H
#define SHADOWENGINE_PLAYER_H

#include "../EntityRegistry.h"
#include "ShadowEntity/SceneEntity.h"


class Player : public ShadowEngine::ShadowEntity::SceneEntity
{
	SHObject_Base(Player)
		Entity_Base(Player, SceneEntity)

public:
	static std::string id;

	void Render() override;
};

#endif //SHADOWENGINE_PLAYER_H

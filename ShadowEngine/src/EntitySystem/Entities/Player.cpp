//
// Created by dpete on 2/17/2019.
//
#include "shpch.h"

#include "Player.h"

	/*
	Entity* Player::Create() {
		Player* res = new Player();

		return res;
	}
	*/

void Player::Render()
{
	std::cout << "Player";
}

void Player::Init()
{
}

void Player::Start()
{
}

void Player::Update(float dt)
{
}

void Player::LateUpdate()
{
}

void Player::LateRender()
{
}

ShadowEngine::EntitySystem::EntityFlags Player::GetFlags()
{
	return ShadowEngine::EntitySystem::EntityFlags::HAS_TICK;
}


//bool Player::registered = ShadowEntity::EntityRegistry::PreRegisterEntity("Player");


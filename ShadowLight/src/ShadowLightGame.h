#pragma once
#include "Core/IGame.h"
#include "Core/ShadowApplication.h"

namespace ShadowLight {

	class ShadowLightGame : public ShadowEngine::IGame
	{
		ShadowEngine::ShadowApplication* app;

	public:
		ShadowLightGame();

		void Init() override;
		void Start() override;
		void Stop() override;
	};
}

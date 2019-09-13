#pragma once

#include "ShadowModules/ShadowModule.h"
#include "ShadowScene/ShadowScene.h"
//Holds the reference to the active scene

namespace ShadowEngine::Scene {

	class SceneManager : public ShadowEngine::ShadowModule
	{
		SHObject_Base(SceneManager)

			ShadowEngine::Scope<ShadowScene> activeScene;


	public:
		SceneManager();

		std::string GetName() override { return "SceneManager"; };

		void Init() override;
		void Update() override;

		void Render() override {};
		void LateRender() override {};

		void LoadEmptyScene();
		void LoadScene(ShadowScene* scene);

		ShadowEngine::Scope<ShadowScene>& GetActiveScene();
	};

}
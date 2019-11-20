#pragma once

#include "ShadowModules/ShadowModule.h"
#include "ShadowScene.h"

//Holds the reference to the active scene

namespace ShadowEngine::EntitySystem {

	class SceneManager : public ShadowEngine::ShadowModule
	{
		SHObject_Base(SceneManager)

			ShadowEngine::Scope<Scene> activeScene;


	public:
		SceneManager();

		std::string GetName() override { return "SceneManager"; };

		void Init() override;
		void Update() override;

		void Render() override {};
		void LateRender() override {};

		void LoadEmptyScene();
		void LoadScene(Scene* scene);

		ShadowEngine::Scope<Scene>& GetActiveScene();
	};

}
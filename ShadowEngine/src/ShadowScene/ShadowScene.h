#pragma once
#include <memory>

#include "Core/SHObject.h"
#include "ShadowEntity/Entity.h"
#include "ShadowEntity/Entities/Camera.h"

namespace ShadowScene {

	class ShadowScene : public ShadowEngine::SHObject, public std::enable_shared_from_this<ShadowScene>
	{
		SHObject_Base(ShadowScene)

	public:
		std::vector<ShadowEngine::Scope<ShadowEntity::Entity>> entities_;

		//Main Camera ref
		Camera* mainCamera;

		ShadowScene() : mainCamera(nullptr) {

		}
		virtual ~ShadowScene() = default;


		virtual void Init();

		//Functions called for each entity
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render();
		virtual void LateRender();

		template<class T>
		T* AddNewInstance()
		{
			entities_.push_back(std::make_unique<T>(this));
			return dynamic_cast<T*>(entities_.back().get());
		}
	};

}
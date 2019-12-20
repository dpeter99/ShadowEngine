#pragma once
#include <memory>

#include "Core/SHObject.h"
#include "Entity.h"
#include "EntityManager.h"

class Camera;

namespace ShadowEngine::EntitySystem {
	
	class Scene : public SHObject, public std::enable_shared_from_this<Scene>
	{
		SHObject_Base(Scene)

	public:
		std::list<rtm_ptr<Entity>> m_entities;

		//Main Camera ref
		Camera* mainCamera;

		Scene() : mainCamera(nullptr) {

		}
		virtual ~Scene() = default;


		virtual void Init();

		//Functions called for each entity
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render();
		virtual void LateRender();

		template<class T, class ...ARGS>
		rtm_ptr<T> AddEntity(ARGS&&... args) {
			rtm_ptr<T> ptr = EntityManager::Instance->AddEntity<T>(std::forward<ARGS>(args)...);
			ptr->scene = this;
			m_entities.push_back(ptr);

			return ptr;
		}

		template<class T>
		void DestroyEntity(rtm_ptr<T>& entity) {
			EntityManager::Instance->RemoveEntity<T>(entity);
			m_entities.remove(entity);
		}

		void DestroyScene() {
			for each (auto var in m_entities)
			{
				EntityManager::Instance->RemoveEntity(var);
			}
		}
	};

}

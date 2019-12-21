#pragma once

#include <string>
#include <iostream>

#include "EntityBase.h"

namespace ShadowEngine::ShadowEntity {
	class Transform;
}

namespace ShadowEngine::EntitySystem
{
	struct SystemCallbacks;
	class Scene;

	class EntityManager;
}

namespace ShadowEngine::EntitySystem
{
	//class Entity;

	template<class Type>
	class rtm_ptr
	{
	private:
		Type* m_ptr;

		int m_uid;

	public:
		rtm_ptr(Type* ptr) : m_ptr(ptr), m_uid(ptr->m_runtimeUID) {}

		rtm_ptr() : m_ptr(nullptr) {}
		
		template<class T>
		rtm_ptr(const rtm_ptr<T>& o) {
			m_ptr = (Type*)o.getInternalPointer();
			m_uid = o.getInternalUID();
		}
		
		Type* operator->() const
		{
			if (m_ptr->m_runtimeUID != m_uid) {
				assert(m_ptr->m_runtimeUID == m_uid);
				return nullptr;
			}
			return ((Type*)m_ptr);
		}

		inline operator bool() const { return m_ptr != nullptr && m_ptr->m_runtimeUID == m_uid; }

		template<class T>
		inline bool operator ==(rtm_ptr<T> o) const {
			return m_ptr == o.m_ptr &&
					m_uid == o.m_uid; 
		}

		template<class T>
		inline operator rtm_ptr<T>() const {
			return rtm_ptr<T>(m_ptr);
		}

		void null() {
			m_ptr = nullptr;
			m_uid = -1;
		}

		void* getInternalPointer() const{
			return (void*)m_ptr; 
		}

		int getInternalUID() const { return m_uid; }

	};

	enum class EntityFlags {
		NONE = 0,
		HAS_TICK = 1 << 0,
		HAS_LATE_TICK = 1 << 1
	};

	/// This is the base entity used in the game world. This should never be instanciated only the derived classes
	/// <summary>
	/// Base Entity in the scene
	/// </summary>
	class Entity : public SHObject
	{
		SHObject_Base(Entity)

	public:
		/// <summary>
		/// This is the Globaly unique ID of this Entity
		/// </summary>
		/// This ID will be only assigned to this Entity instance
		/// It can be used to look up entities, but it is not recommended as it is a slow process
		/// For Entity Lookup use the m_runtimeIndex
		int m_runtimeUID;

		/// <summary>
		/// This is the UID that represents an invalid ID
		/// </summary>
		static const int INVALID_UID = -1;


		/// <summary>
		/// This is the ID of the entity usable for lookup
		/// </summary>
		/// This ID will be reused when the Entity is removed
		/// 
		/// To use this Entity for lookup use the LUT in the EntityManager
		int m_runtimeIndex;

		///The name of this entity
		std::string name;

		
		/// <summary>
		/// The scene this Enity is assigned to
		/// </summary>
		Scene* scene;

		/**
		 * \brief the internal hierarchy of this Entity
		*/
		std::vector<rtm_ptr<Entity>> internalHierarchy;

		std::vector<rtm_ptr<Entity>> hierarchy;

		rtm_ptr<Entity> parent;

	public:
		/// <summary>
		/// Empty default constructor
		/// </summary>
		Entity();

		/// <summary>
		/// Constructor defining the scene it is located in
		/// </summary>
		/// <param name="scene">The scene that this entity is in</param>
		Entity(Scene* scene);

		virtual ~Entity() {}

		/// <summary>
		/// Creates a new Entity
		/// </summary>
		/// <param name="scene">The scene that this entity is in</param>
		/// <returns>Pointer to the Entity created</returns>
		virtual Entity* Create(Scene* scene);

		virtual void Build() {};
		
		/// Called when the Entity needs to be initialised. Should be used as a constructor
		/// <summary>
		/// Called when the Entity needs to be initialised.
		/// </summary>
		virtual  void Init() {};

		/// <summary>
		/// Called when the world starts or before the Entity get's it's first tick
		/// </summary>
		virtual void Start() {};

		/// <summary>
		/// Called every tick
		/// </summary>
		virtual void Update(float dt) {};

		/// <summary>
		/// Called every Tick after the first is finished
		/// </summary>
		virtual void LateUpdate() {};

		virtual void Render() {};

		virtual  void LateRender() {};

		virtual EntityFlags GetFlags();

		

		virtual ShadowEntity::Transform* GetTransform();
	public:
		//Internal call
		virtual void ParentTransformUpdated()
		{
			TransformChanged();
		};
	public:
		//Override for custom behaviour on transform change
		virtual void TransformChanged() {};

		
	public:
		/// <summary>
		/// Sets the scene this Entity is in
		/// </summary>
		/// <param name="se">The scene this entity belongs to</param>
		void SetScene(Scene* se);

		virtual void SetParent(rtm_ptr<Entity> e);


		template<class T, class ...ARGS>
		rtm_ptr<T> AddChildEntity(ARGS&&... args) {
			rtm_ptr<T> ptr = EntityManager::Instance->AddEntity<T>(std::forward<ARGS>(args)...);
			ptr->scene = scene;
			hierarchy.push_back(ptr);
			ptr->SetParent(this);

			return ptr;
		}

		template<class T, class ...ARGS>
		rtm_ptr<T> AddInternalChildEntity(ARGS&&... args) {
			rtm_ptr<T> ptr = EntityManager::Instance->AddEntity<T>(std::forward<ARGS>(args)...);
			ptr->scene = scene;
			internalHierarchy.push_back(ptr);
			ptr->SetParent(this);

			return ptr;
		}

	public:
		friend std::ostream& operator<<(std::ostream& os, const Entity& dt);

	public:
		template<class T>
		static void UpdateEntities(EntityManager* mgr, float dt)
		{
			EntityContainer<T>& container = *mgr->GetContainerByType<T>();

			int c = 0;

			for each (auto & current in container)
			{
				current.Update(dt);
			}
		}

		template<class T>
		static void InitEntities(EntityManager* mgr)
		{
			auto& container = *mgr->GetContainerByType<T>();

			int c = 0;

			for each (auto & current in container)
			{
				current.Init();
			}
		}

		template<class T>
		static void RegisterDefaultUpdate(EntityManager& mgr) {
			SystemCallbacks s;
			s.update = &UpdateEntities<T>;
			s.init = &InitEntities<T>;

			mgr.AddSystem(s);
		}
	};
}

#pragma once

#include <string>
#include <iostream>

//#include "ShadowScene/ShadowScene.h"

#include "EntityBase.h"

namespace ShadowEngine::Scene
{
	class ShadowScene;
}

namespace ShadowEngine::ShadowEntity
{
	enum class EntityFlags {
		NONE = 0,
		HAS_TICK= 1 << 0,
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

		Scene::ShadowScene* scene;
		
	public:
		/// <summary>
		/// Empty default constructor
		/// </summary>
		Entity();

		/// <summary>
		/// Constructor defining the scene it is located in
		/// </summary>
		/// <param name="scene">The scene that this entity is in</param>
		Entity(Scene::ShadowScene* scene);

		/// <summary>
		/// Creates a new Entity
		/// </summary>
		/// <param name="scene">The scene that this entity is in</param>
		/// <returns>Pointer to the Entity created</returns>
		virtual Entity* Create(Scene::ShadowScene* scene);

		/// Called when the Entity needs to be initialised. Should be used as a constructor
		/// <summary>
		/// Called when the Entity needs to be initialised.
		/// </summary>
		virtual  void Init();
		
		/// <summary>
		/// Called when the world starts or before the Entity get's it's first tick
		/// </summary>
		virtual void Start();

		/// <summary>
		/// Called every tick
		/// </summary>
		virtual void Update();

		/// <summary>
		/// Called every Tick after the first is finished
		/// </summary>
		virtual void LateUpdate();

		virtual void Render();

		virtual  void LateRender();

		virtual EntityFlags GetFlags();

	public:
		/// <summary>
		/// Sets the scene this Entity is in
		/// </summary>
		/// <param name="se">The scene this entity belongs to</param>
		void SetScene(Scene::ShadowScene* se);

		friend std::ostream& operator<<(std::ostream& os, const Entity& dt);
	};
}

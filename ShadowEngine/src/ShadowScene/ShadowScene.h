#pragma once
#include <memory>

#include "Core/SHObject.h"
#include "ShadowEntity/Entity.h"
#include "ShadowEntity/Entities/Camera.h"

class ShadowScene : public SHObject, public std::enable_shared_from_this<ShadowScene>
{
	SHObject_Base(ShadowScene)

public:
	std::list<ShadowEngine::Scope<ShadowEntity::Entity>> entities_;

	//Main Camera ref
	Camera* mainCamera;

	virtual void Init();

	//Functions called for each entity
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();

	virtual void Render();
	virtual void LateRender();

	template<class T, class... _Types>
	void AddNewInstance(_Types&&... _Args)
	{
		ShadowEngine::Ref<T> ent = std::make_unique<T>(_Args...);
		ent->SetScene(this);
		entities_.push_back(ent);
	}
};


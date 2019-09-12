#pragma once
#include <memory>

#include "Core/SHObject.h"
#include "ShadowEntity/Entity.h"
#include "ShadowEntity/Entities/Camera.h"

class ShadowScene : public SHObject, public std::enable_shared_from_this<ShadowScene>
{
	SHObject_Base(ShadowScene)

public:
	std::vector<ShadowEngine::Scope<ShadowEntity::Entity>> entities_;

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
		entities_.push_back(std::make_shared<T>(this));
	}
};


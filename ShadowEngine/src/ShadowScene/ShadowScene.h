#pragma once
#include <memory>

#include "Core/SHObject.h"
#include "ShadowEntity/Entity.h"

class ShadowScene : public SHObject
{
	SHObject_Base(ShadowScene)

public:
	std::list<ShadowEngine::Ref<ShadowEntity::Entity>> entities_;

	//Main Camera ref

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
		auto ent = make_shared <T>(_Args);
		ent->SetScene(this);
		entities_.push_back(ent);
	}
};


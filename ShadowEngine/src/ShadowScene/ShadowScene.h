#pragma once
#include "Core/SHObject.h"
#include "ShadowEntity/Entity.h"

class ShadowScene : public SHObject
{
	SHObject_Base(ShadowScene)
	
public:
		std::list<ShadowEntity::Entity> entities_;
		
};


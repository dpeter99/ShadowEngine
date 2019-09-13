#pragma once
#include "Core/SHObject.h"

namespace ShadowEngine::Debug {

	class Inspector :
		public ShadowEngine::SHObject
	{
		SHObject_Base(Inspector)

	public:
		virtual void Draw(SHObject& obj) = 0;
	};

}
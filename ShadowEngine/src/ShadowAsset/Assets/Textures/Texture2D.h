#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "Texture.h"


namespace ShadowEngine::Assets {


	class Texture2D : public Texture
	{
		SHObject_Base(Texture2D)

	protected:


	public:
		Texture2D(std::string path);
		Texture2D();

	};


	class Texture2DImpl : public TextureImpl {
	public:
		static Ref<Texture2DImpl> Create(std::string path);


	};
}

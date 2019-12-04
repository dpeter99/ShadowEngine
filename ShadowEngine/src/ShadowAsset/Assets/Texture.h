#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"

namespace ShadowEngine::Assets {

	class Texture2DImpl {
	public:
		static Ref<Texture2DImpl> Create(std::string path);

		virtual void Upload() = 0;
	};

	class Texture : public ShadowAsset
	{
		SHObject_Base(Texture)

		//virtual uint32_t GetWidth() const = 0;
		//virtual uint32_t GetHeight() const = 0;

	public:
		Texture();

	};

	class Texture2D : public Texture
	{
		SHObject_Base(Texture2D)

	public:
		Texture2D();

	};
}
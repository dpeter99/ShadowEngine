#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

namespace ShadowEngine::Assets {

	class TextureImpl {
	public:
		virtual void Upload() = 0;
	};

	class Texture2DImpl : public TextureImpl {
	public:
		static Ref<Texture2DImpl> Create(std::string path);


	};

	class Texture : public ShadowAsset
	{
		SHObject_Base(Texture)
	protected:
		Ref<TextureImpl> impl;


		//virtual uint32_t GetWidth() const = 0;
		//virtual uint32_t GetHeight() const = 0;

	public:
		Texture(std::string path);
		//Texture();

		virtual Ref<TextureImpl> getImpl() { return impl; };

		void Upload() { impl->Upload(); };
	};

	class Texture2D : public Texture
	{
		SHObject_Base(Texture2D)

	protected:


	public:
		Texture2D(std::string path);
		Texture2D();

	};
}
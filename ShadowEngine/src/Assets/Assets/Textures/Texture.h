#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "Assets/ShadowAsset.h"

namespace ShadowEngine::Assets {

	/// <summary>
	/// The Rendering backend implements this and get's it by calling <see cref="Texture.getImpl()">getImpl</see>
	/// </summary>
	class TextureImpl {
	public:
		virtual void Upload() = 0;
	};


	/// <summary>
	/// The texture asset
	/// </summary>
	/// 
	/// Texture asset, representing any kind of texture.
	class Texture : public ShadowAsset
	{
		SHObject_Base(Texture)
	protected:
		Ref<TextureImpl> impl;


		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetZ() const = 0;
 
	public:
		Texture(std::string path);
		Texture();

		virtual Ref<TextureImpl> getImpl() { return impl; };

		void Upload() { impl->Upload(); }
		//virtual void Load(SFF::SFFElement& root) override = 0;
	};


}
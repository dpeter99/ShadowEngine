#pragma once

#include "Core/SHObject.h"
#include "Texture.h"

namespace ShadowEngine::Assets {

	class TextureCubeMap;

	/// <summary>
	/// This is the actual Renderer side implementation of the cube map.
	/// It has a reference to the actual asset it represents.
	/// </summary>
	class TextureCubeMapImpl : public TextureImpl {
	public:
		
		static Ref<TextureCubeMapImpl> Create(TextureCubeMap* asset);

		/// <summary>
		/// The asset that this represents.
		/// </summary>
		TextureCubeMap* asset;

		/// <summary>
		/// Constructor for the Cube Map Texture Implementation
		/// </summary>
		/// <param name="asset"></param>
		TextureCubeMapImpl(TextureCubeMap* asset)
		{
			this->asset = asset;
		}

	};
	
	class TextureCubeMap : public Texture
	{
		SHObject_Base(TextureCubeMap)
	private:
		std::string up_texture;
		std::string down_texture;
		std::string front_texture;
		std::string back_texture;
		std::string left_texture;
		std::string right_texture;


	public:
		explicit TextureCubeMap(const std::string& path);
		TextureCubeMap();

		//Ref<TextureImpl> getImpl() override { return impl; }
		~TextureCubeMap() override {};

		std::string GetTexturePath(int i);

		// Inherited via Texture
		virtual void Load(SFF::SFFElement& root, Assets::FileSystem::Path path) override;

		virtual uint32_t GetWidth() const override;

		virtual uint32_t GetHeight() const override;

		virtual uint32_t GetZ() const override;

	};


}
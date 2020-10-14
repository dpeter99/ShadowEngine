#pragma once

#include "Core/Core.h"
#include "Texture.h"


namespace ShadowEngine::Assets {
	class Texture2DImpl;


	class Texture2D : public Texture
	{
		SHObject_Base(Texture2D)

	protected:
		std::string texture;

	public:
		Texture2D(std::string path);
		Texture2D();

		~Texture2D() override = default;

		
		//Ref<TextureImpl> getImpl() override { return impl; }

		std::string GetTexturePath();

		void Load(SFF::SFFElement& root, FileSystem::Path path) override;
		
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		uint32_t GetZ() const override;
		
	};

	/// <summary>
	/// This is the actual Renderer side implementation of the 2D Texture.
	/// It has a reference to the actual asset it represents.
	/// </summary>
	class Texture2DImpl : public TextureImpl {
	public:
		static Ref<Texture2DImpl> Create(Texture2D* asset);

		/// <summary>
		/// The asset that this represents.
		/// </summary>
		Texture2D* asset;

		/// <summary>
		/// Constructor for the Cube Map Texture Implementation
		/// </summary>
		/// <param name="asset"></param>
		Texture2DImpl(Texture2D* asset)
		{
			this->asset = asset;
		}
	};
}

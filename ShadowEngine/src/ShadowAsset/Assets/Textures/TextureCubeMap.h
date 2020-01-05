#pragma once

#include "Core/SHObject.h"
#include "Texture.h"

namespace ShadowEngine::Assets {


	class TextureCubeMapImpl : public TextureImpl {
	public:
		static Ref<TextureCubeMapImpl> Create(std::string path);


	};
	
	class TextureCubeMap :
		public Texture
	{
		SHObject_Base(TextureCubeMap)
		
	public:
		explicit TextureCubeMap(const std::string& path);

		Ref<TextureImpl> getImpl() override { return impl; }
		~TextureCubeMap() override {};

		
	};


}
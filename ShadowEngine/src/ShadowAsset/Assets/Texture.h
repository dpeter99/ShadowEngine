#pragma once
#include "Core/Core.h"
#include "Core/SHObject.h"
#include "ShadowAsset/ShadowAsset.h"

#include "ShadowRenderer/Buffer.h"

namespace ShadowEngine::Assets {

	class Texture : public ShadowAsset
	{
		SHObject_Base(Texture)

	public:
		Texture();

	};

	class Texture2D : public ShadowAsset
	{
		SHObject_Base(Texture2D)

	public:
		Texture2D();

	};
}
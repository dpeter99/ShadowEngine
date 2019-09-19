#pragma once

#include <string>

namespace ShadowEngine::Assets {

	class ShadowAsset
	{
	public:
		int runtimeAssetID;
		std::string path;


		ShadowAsset();
		virtual ~ShadowAsset();
	};
}
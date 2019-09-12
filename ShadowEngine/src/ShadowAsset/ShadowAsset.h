#pragma once

#include <string>

namespace ShadowAssets {

	class ShadowAsset
	{
	public:
		int runtimeAssetID;
		std::string path;


		ShadowAsset();
		virtual ~ShadowAsset();
	};
}
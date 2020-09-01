#include "shpch.h"
#include "Path.h"

#include "Assets/AssetManager.h"

namespace ShadowEngine::Assets::FileSystem {

	std::string Path::GetFullPath() const {
		std::string final_path = AssetManager::getInstance()->GetRootPath();
		final_path += AssetManager::getInstance()->GetAssetPack(this->pack)->GetPath();
		final_path += this->path;
		return final_path;
	}


}
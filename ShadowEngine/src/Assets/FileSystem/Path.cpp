#include "shpch.h"
#include "Path.h"

#include "Assets/AssetManager.h"

namespace ShadowEngine::Assets::FileSystem {

	std::string Path::GetFullPath() const {
		std::string final_path = AssetManager::getInstance()->GetRootPath();
		final_path += AssetManager::getInstance()->GetAssetPack(this->pack)->GetPath();
		final_path += this->path.generic_string();
		return final_path;
	}

	std::string Path::GetFullFolderPath() const
	{
		std::string final_path = AssetManager::getInstance()->GetRootPath();
		final_path += AssetManager::getInstance()->GetAssetPack(this->pack)->GetPath();
		final_path += this->path.parent_path().generic_string() + "/";
		return final_path;
	}

	inline std::string Path::GetPath() const {
		return pack + ":" + path.generic_string();
	}


}
#include "AssetManager.h"
#include "AssetLoader.h"


AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

bool AssetManager::CheckLoaded(std::string path, ShadowAsset** asset = nullptr)
{
	for (auto item : this->loadedAssets) {
		if (item.second->path == path) return true;
		if(asset != nullptr)
		* asset = item.second;
	}

	if (asset != nullptr)
		* asset = nullptr;

	return false;
}

void AssetManager::UnloadAsset(std::string)
{

}

void AssetManager::UnloadAsset(ShadowAsset* asset)
{
	auto v = this->loadedAssets.find(asset->runtimeAssetID);
	this->loadedAssets.erase(v);
	delete asset;
}


template <> ShadowWorld* AssetManager::GetAsset<ShadowWorld>(std::string path)
{
	ShadowAsset* f;

	if(CheckLoaded(path, &f))
	{
		return dynamic_cast<ShadowWorld*>(f);
	}

	ShadowWorld* w;

	w = AssetLoader::LoadWorld(path);
	this->loadedAssets[nextID] = w;
	w->path = path;
	w->id = nextID;
	nextID++;
	return w;
}



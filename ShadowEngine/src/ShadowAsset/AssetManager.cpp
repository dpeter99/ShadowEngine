#include "shpch.h"

#include "AssetManager.h"
#include "AssetLoader.h"

#include "ShadowFileFormat/SFFParser.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager()
{
	instance = this;
}


AssetManager::~AssetManager()
{
}

void AssetManager::Init()
{
	SH_CORE_INFO("Trying to load Resources/pack.spf");
	SFFElement* root = ShadowEngine::SFF::SFFParser::ReadFromFile("./Resources/pack.spf");
	if(root == nullptr)
	{
		SH_CORE_CRITICAL("Coudn't load pack file.");
		return;
	}
	
	auto* assets = root->GetChildByName("Assets");
	for each (auto& var in assets->children)
	{
		this->knownAssets.emplace(std::stoi(var.first),var.second->value);
	}
	
}

bool AssetManager::CheckLoaded(std::string path, ShadowEngine::Assets::ShadowAsset** asset = nullptr)
{
	for (auto item : this->loadedAssets)
	{
		if (item.second->path == path) return true;
		if (asset != nullptr)
			* asset = item.second;
	}

	if (asset != nullptr)
		* asset = nullptr;

	return false;
}

void AssetManager::UnloadAsset(std::string)
{
}

void AssetManager::UnloadAsset(ShadowEngine::Assets::ShadowAsset* asset)
{
	auto v = this->loadedAssets.find(asset->runtimeAssetID);
	this->loadedAssets.erase(v);
	delete asset;
}

/*

template<class T>
static T* AssetManager::GetAsset(std::string path)
{
	ShadowAsset* f;

	if (CheckLoaded(path, &f))
	{
		return dynamic_cast<T*>(f);
	}

	T* w;

	w = AssetLoader::LoadAsset(path);
	AssetManager::instance->loadedAssets[nextID] = w;
	w->path = path;
	w->id = nextID;
	nextID++;
	return w;
}
*/

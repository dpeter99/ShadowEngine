#include "shpch.h"

#include "AssetManager.h"
#include "AssetLoader.h"

#include "ShadowFileFormat/SFFParser.h"



bool ShadowEngine::Assets::AssetInfo::operator==(const std::vector<std::string>& search_tags) const
{
	const std::vector<std::string>& asset_tags = tags;
	auto pred = [&asset_tags](const std::string& tag)
	{
		return std::any_of(asset_tags.begin(), asset_tags.end(), [&tag](std::string t) {return t == tag; });
	};
	return std::all_of(search_tags.begin(), search_tags.end(),pred);
}




ShadowEngine::Assets::AssetManager* ShadowEngine::Assets::AssetManager::instance = nullptr;

ShadowEngine::Assets::AssetManager::AssetManager()
{
	instance = this;
}

ShadowEngine::Assets::AssetManager::~AssetManager()
{
}


void ShadowEngine::Assets::AssetManager::Init()
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
		AssetInfo info(std::stoi(var.first), var.second->value);
		
		this->knownAssets.emplace(info);
	}
	
}

bool ShadowEngine::Assets::AssetManager::CheckLoaded(std::string path, ShadowEngine::Assets::ShadowAsset** asset = nullptr)
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

void ShadowEngine::Assets::AssetManager::UnloadAsset(std::string)
{
}

void ShadowEngine::Assets::AssetManager::UnloadAsset(ShadowEngine::Assets::ShadowAsset* asset)
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

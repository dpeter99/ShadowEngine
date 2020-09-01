#include "shpch.h"

#include "AssetManager.h"
#include "AssetLoader.h"

#include "ShadowFileFormat/SFFParser.h"

namespace ShadowEngine::Assets {

	const ShadowAsset* AssetInfo::getAsset() const {
		if (loaded)
			return asset;
		else {
			SH_CORE_ERROR("{0} is not loaded yet", (std::string)this->path);
			return nullptr;
		}

	}

}

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

	SetRootPath("./Resources/");
}

ShadowEngine::Assets::AssetManager::~AssetManager()
{
}


void ShadowEngine::Assets::AssetManager::Init()
{
	//Load each pack that was added to the list
	for (auto& pack : this->assetPacks)
	{
		SH_CORE_INFO("Trying to load {0}", pack->GetName());

		std::string path = pack->GetPath();
		path = root_path + path;

		SFF::SFFElement* root = ShadowEngine::SFF::SFFParser::ReadFromFile(path + "/pack.spf");
		if (root == nullptr)
		{
			SH_CORE_CRITICAL("Coudn't load pack file, for {0}", pack->GetName());
			return;
		}

		auto* assets = root->GetChildByName("Assets");
		for each (auto & var in assets->children)
		{
			std::string path = pack->GetID();
			path += ":";
			path += var.second->value;

			AssetInfo info((UUID)std::stoi(var.first), this->GUID_next++, path, pack);

			this->knownAssets.emplace(info);
		}
	}
	
}

bool ShadowEngine::Assets::AssetManager::CheckLoaded(std::string path, OUT ShadowEngine::Assets::ShadowAsset** asset = nullptr)
{
	/*
	for (auto item : this->knownAssets)
	{
		if (item.second->path == path) return true;
		if (asset != nullptr)
			* asset = item.second;
	}

	if (asset != nullptr)
		* asset = nullptr;
	*/
	return false;
}

void ShadowEngine::Assets::AssetManager::UnloadAsset(std::string)
{
}

void ShadowEngine::Assets::AssetManager::UnloadAsset(ShadowEngine::Assets::ShadowAsset* asset)
{
	//auto v = this->loadedAssets.find(asset->runtimeAssetID);
	//this->loadedAssets.erase(v);
	//delete asset;
}

/*

template<class T>
static T* AssetManager::GetAsset_OLD(std::string path)
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

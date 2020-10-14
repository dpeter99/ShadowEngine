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

	void AssetInfo::SetLoaded(ShadowAsset* asset) {
		if (asset != nullptr) {
			this->asset = asset;
			this->loaded = true;
		}
		else {
			this->asset = nullptr;
			this->loaded = false;
		}
	}


	bool AssetInfo::operator==(const FileSystem::Path& name) const
	{
		return this->path == name;
	}

	bool AssetInfo::operator!=(const std::string& name) const
	{
		return !(*this == name);
	}

	bool AssetInfo::operator==(UUID uuid) const
	{
		return this->uuid == uuid;
	}

	bool AssetInfo::operator!=(UUID uuid) const
	{
		return !(*this == uuid);
	}


	bool AssetInfo::operator==(const std::vector<std::string>& search_tags) const
	{
		const std::vector<std::string>& asset_tags = tags;
		auto pred = [&asset_tags](const std::string& tag)
		{
			return std::any_of(asset_tags.begin(), asset_tags.end(), [&tag](std::string t) {return t == tag; });
		};
		return std::all_of(search_tags.begin(), search_tags.end(),pred);
	}

	bool AssetInfo::operator!=(const std::vector<std::string>& search_tags) const {
		return !(*this == search_tags);
	}

	bool AssetInfo::HasTag(const std::string& tag) const
	{
		return std::find(tags.begin(), tags.end(), tag) != tags.end();
	}



	AssetManager* AssetManager::instance = nullptr;

	AssetManager::AssetManager()
	{
		instance = this;

		SetRootPath("./Resources/");
	}

	AssetManager::~AssetManager() = default;

	void AssetManager::Init()
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

				//AssetInfo info();

				auto info = std::make_shared<AssetInfo>((UUID)std::stoi(var.first), this->GUID_next++, path, pack);

				//this->knownAssets.emplace(info);
				this->knownAssets.emplace(info->GetGlobalUUID(), info);

				//this->teszt.emplace(0, AssetInfo((UUID)std::stoi(var.first), this->GUID_next++, path, pack));
			}
		}

	}



	void AssetManager::SetRootPath(const std::string& path) {
		root_path = path;
	}

	const std::string& AssetManager::GetRootPath() const {
		return root_path;
	}

	void AssetManager::AddAssetPack(std::string name, std::string id, std::string path) {
		if (loaded) {
			SH_CORE_ERROR("Asset Pack can only be added on statup");
			return;
		}

		//TODO: Check if the pack is already present
		Ref<FileSystem::AssetPack> pack_poiner = std::make_shared<FileSystem::AssetPack>(name, id, path);
		assetPacks.push_back(pack_poiner);
	}

	Ref<FileSystem::AssetPack> AssetManager::GetAssetPack(std::string id) {
		auto pack = std::find_if(assetPacks.begin(), assetPacks.end(), [id](Ref<FileSystem::AssetPack>& item) {return id == item->GetID(); });
		if (pack == assetPacks.end()) {
			SH_CORE_ERROR("Can't find pack '{0}'", id);
		}
		return *pack;
	}

	
	bool AssetManager::CheckLoaded(std::string path, OUT ShadowEngine::Assets::ShadowAsset** asset = nullptr)
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

	void AssetManager::UnloadAsset(std::string)
	{
	}



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

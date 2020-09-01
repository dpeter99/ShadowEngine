#pragma once
#include "ShadowModules/ShadowModule.h"

#include "ShadowAsset.h"

#include "FileSystem/AssetPack.h"
#include "FileSystem/Path.h"

#include "ShadowMap/ShadowWorld.h"
#include "AssetLoader.h"

#include "ShadowFileFormat/SFFParser.h"

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cinttypes>
#include <functional>
#include <set>
//#include <concepts>



namespace ShadowEngine::Assets {

	typedef uint64_t UUID;

	/// <summary>
	/// Contains metadta about the asset
	/// </summary>
	class AssetInfo
	{
		/// <summary>
		/// UUID that is unique inside the asset pack
		/// </summary>
		UUID uuid;

		/// <summary>
		/// UUID the is unique for all assets
		/// </summary>
		UUID global;

		FileSystem::Path path;
		std::vector<std::string> tags;

		Ref<FileSystem::AssetPack> pack;

		bool loaded;
		ShadowAsset* asset;

	public:
		AssetInfo(UUID uuid, UUID global, std::string path, Ref<FileSystem::AssetPack> pack) : 
			uuid(uuid),
			global(global),
			path(path),
			pack(pack)
		{
			loaded = false;
			asset = nullptr;
		}

		const std::string& getName() const
		{
			return "Not implemented yet :(";
		}

		const FileSystem::Path& getPath() const {
			return path;
		}

		const UUID& getUUID() const
		{
			return uuid;
		}

		const UUID& GetGlobalUUID() const {
			return global;
		}

		const bool getLoaded() const
		{
			return loaded;
		}

		const ShadowAsset* getAsset() const;


		void SetLoaded(ShadowAsset* asset) {
			if (asset != nullptr) {
				this->asset = asset;
				this->loaded = true;
			}
			else {
				this->asset = nullptr;
				this->loaded = false;
			}
		}


		bool operator==(const FileSystem::Path& name) const
		{
			return this->path == name;
		}

		bool operator!=(const std::string& name) const
		{
			return !(*this == name);
		}

		bool operator==(UUID uuid) const
		{
			return this->uuid == uuid;
		}

		bool operator!=(UUID uuid) const
		{
			return !(*this == uuid);
		}

		/// <summary>
		/// Operator for comparing with serach tags
		/// </summary>
		/// <param name="search_tags">The tags that the asset needs to incude in order to match</param>
		/// <returns></returns>
		bool operator==(const std::vector<std::string>& search_tags) const;

		bool operator!=(const std::vector<std::string>& search_tags) const {
			return !(*this == search_tags);
		}

		bool HasTag(const std::string& tag) const
		{
			return std::find(tags.begin(), tags.end(), tag) != tags.end();
		}

	};

	struct asset_info_comparator {
		bool operator() (const AssetInfo& a, const AssetInfo& b) const
		{
			return a.GetGlobalUUID() < b.GetGlobalUUID();
		}
	};

	//Responsible for loading and unloading assets at runtime
	class AssetManager : public ShadowEngine::ShadowModule
	{

		SHObject_Base(AssetManager)

	private:
		//Singletom object
		static AssetManager* instance;

		std::string root_path = "";

		bool loaded = false;

		UUID GUID_next = 0;
	public:

		static AssetManager* getInstance()
		{
			return instance;
		}

		typedef std::set<AssetInfo, asset_info_comparator> AssetInfoList;
		AssetInfoList knownAssets;

		std::vector<Ref<FileSystem::AssetPack>> assetPacks;

		//A map where the loaded assets are stored
		//Maps the id to the ShadowAsset
		//[[deprecated("Use knownAssets")]]
		//std::map<int, ShadowEngine::Assets::ShadowAsset*> loadedAssets;

		int nextID = 0;

		AssetManager();
		~AssetManager();

		void PreInit() override {};
		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override {};
		std::string GetName() override { return "Asset Manager"; };

		//###################################
		//Root path
		//###################################

		/// <summary>
		/// Sets the base directory for asset lookups
		/// </summary>
		/// <param name="path"></param>
		void SetRootPath(const std::string& path) {
			root_path = path;
		}

		const std::string& GetRootPath() const {
			return root_path;
		}

		//###################################
		//Asset Packs
		//###################################

		/// <summary>
		/// Registers an asset pack for loading on int
		/// </summary>
		/// <param name="name"></param>
		/// <param name="id"></param>
		/// <param name="path"></param>
		void AddAssetPack(std::string name, std::string id, std::string path) {
			if (loaded) {
				SH_CORE_ERROR("Asset Pack can only be added on statup");
				return;
			}

			//TODO: Check if the pack is already present
			Ref<FileSystem::AssetPack> pack_poiner = std::make_shared<FileSystem::AssetPack>(name, id, path);
			assetPacks.push_back(pack_poiner);
		}

		Ref<FileSystem::AssetPack> GetAssetPack(std::string id) {
			auto pack = std::find_if(assetPacks.begin(), assetPacks.end(), [id](Ref<FileSystem::AssetPack>& item) {return id == item->GetID(); });
			if (pack == assetPacks.end()) {
				SH_CORE_ERROR("Can't find pack '{0}'", id);
			}
			return *pack;
		}

		//###################################
		//Assets
		//###################################

		//Checks if the asset is loaded
		bool CheckLoaded(std::string path, ShadowEngine::Assets::ShadowAsset** asset);

		//Cleans up a asset based on it's path
		void UnloadAsset(std::string);
		void UnloadAsset(ShadowEngine::Assets::ShadowAsset* asset);

		//Gets the needed asset based on it's path
		//Makes sure it will be cleaned up when the game exits
		//This sets up the ShadowAsset base class
		template <class T>
		static T* GetAsset_OLD(std::string path)
		{
			ShadowEngine::Assets::ShadowAsset* f;

			if (instance->CheckLoaded(path, &f))
			{
				return dynamic_cast<T*>(f);
			}

			T* w = ShadowEngine::Assets::AssetLoader::LoadAsset<T>(path);
			if (w == nullptr)
				return nullptr;

			instance->loadedAssets[instance->nextID] = w;
			w->path = path;
			w->runtimeAssetID = instance->nextID;
			instance->nextID++;
			return w;
		}

		/*
		template<class T>
		concept asset = requires{ std::derived_from<ShadowAsset, T> };
		*/

		/// <summary>
		/// Loads an asset based on the suplied asset path
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="path"></param>
		/// <returns></returns>
		template <class T>
		T* GetAsset(const FileSystem::Path path)
		{
			AssetInfoList::iterator& info = std::find_if(knownAssets.begin(), knownAssets.end(), [&path](AssetInfo& asset) {return asset.getPath() == path; });

			if (info == knownAssets.end())
			{
				SH_CORE_WARN("Unknown asset: '{0}'", (std::string)path);
				return nullptr;
			}

			if (info->getLoaded()) {
				return (T*)info->getAsset();
			}

			//Load in the asset
			std::string full_path = path.GetFullPath();
			auto root = SFF::SFFParser::ReadFromFile(full_path);

			T* asset = new T();
			asset->Load(*root, path);

			info->SetLoaded(asset);

			return asset;
		}

	};

}

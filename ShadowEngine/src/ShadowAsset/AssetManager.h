#pragma once
#include "ShadowModules/ShadowModule.h"

#include "ShadowAsset.h"
#include "ShadowMap/ShadowWorld.h"
#include "AssetLoader.h"

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

	class AssetInfo
	{
		UUID uuid;
		std::string name;
		std::vector<std::string> tags;
		
		bool loaded;
		ShadowAsset* asset;

	public:
		AssetInfo(UUID uuid, std::string name)
		{
			this->uuid = uuid;
			this->name = name;

			loaded = false;
			asset = nullptr;
		}
		
		const std::string& getName() const
		{
			return name;
		}

		const UUID& getUUID() const
		{
			return uuid;
		}

		const bool getLoaded() const
		{
			return loaded;
		}
		
		bool operator==(const std::string& name) const
		{
			return this->name.compare(name) == 0;
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
			return a.getUUID() < b.getUUID();
		}
	};
	
	//Responsible for loading and unloading assets at runtime
	class AssetManager : public ShadowEngine::ShadowModule
	{
		//Singletom object ShadowEngine::Reference
		SHObject_Base(AssetManager)

	private:
		static AssetManager* instance;


	public:

		static AssetManager* getInstance()
		{
			return instance;
		}

		std::set<AssetInfo, asset_info_comparator> knownAssets;

		//A map where the loaded assets are stored
		//Maps the id to the ShadowAsset
		[[deprecated("Use knownAssets")]]
		std::map<int, ShadowEngine::Assets::ShadowAsset*> loadedAssets;

		int nextID = 0;

		AssetManager();
		~AssetManager();

		void PreInit() override {};
		void Init() override;
		void Update() override {};
		void Render() override {};
		void LateRender() override {};
		std::string GetName() override { return "Asset Manager"; };

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

		template <class T>
		T* GetAsset(const std::string& path)
		{
			auto& info = std::find_if(knownAssets.begin(), knownAssets.end(), [&path](AssetInfo& asset) {return asset.getName() == path; });

			if (info == knownAssets.end())
			{
				SH_CORE_WARN("Unknown asset: '{0}'", path);
			}

			T* asset = new T();

			return asset;
		}

	};

}

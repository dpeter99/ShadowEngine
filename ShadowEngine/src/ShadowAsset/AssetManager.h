#pragma once
#include "ShadowAsset.h"
#include "ShadowMap/ShadowWorld.h"
#include <map>
#include "AssetLoader.h"


//Responsible for loading and unloading assets at runtime

class AssetManager : public ShadowEngine::ShadowModule
{
	//Singletom object ShadowEngine::Reference
private:
	static AssetManager* instance;


public:

	static AssetManager* getInstance()
	{
		return instance;
	}

	//A map where the loaded assets are stored
	//Maps the id to the ShadowAsset
	std::map<int, ShadowEngine::Assets::ShadowAsset*> loadedAssets;

	int nextID = 0;

	AssetManager();
	~AssetManager();


	//Checks if the asset is loaded
	bool CheckLoaded(std::string path, ShadowEngine::Assets::ShadowAsset** asset);

	//Cleans up a asset based on it's path
	void UnloadAsset(std::string);
	void UnloadAsset(ShadowEngine::Assets::ShadowAsset* asset);

	//Gets the needed asset based on it's path
	//Makes sure it will be cleaned up when the game exits
	//This sets up the ShadowAsset base class
	template <class T>
	static T* GetAsset(std::string path)
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
};

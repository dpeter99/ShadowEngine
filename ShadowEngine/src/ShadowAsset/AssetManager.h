#pragma once
#include "ShadowAsset.h"
#include "ShadowMap/ShadowWorld.h"
#include <map>


//Responsible for loading and unloading assets at runtime

class AssetManager
{
public:
	//Singletom object reference
	static AssetManager* instace;


	//A map where the loaded assets are stored
	//Maps the id to the ShadowAsset
	std::map<int, ShadowAsset*> loadedAssets;

	int nextID = 0;

	AssetManager();
	~AssetManager();



	//Gets the needed asset based on it's path
	//Makes sure it will be cleaned up when the game exits
	//This sets up the ShadowAsset base class
	template<class T> T* GetAsset(std::string path);

	//Checks if the asset is loaded
	bool CheckLoaded(std::string path,ShadowAsset** asset);

	//Cleans up a asset based on it's path
	void UnloadAsset(std::string);
	void UnloadAsset(ShadowAsset* asset);

};



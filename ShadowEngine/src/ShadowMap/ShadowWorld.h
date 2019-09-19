#pragma once

#include <list>
#include <map>

#include "ShadowMapChunk.h"
#include "ShadowAsset/ShadowAsset.h"

namespace ShadowEngine::World {

	//World
	// - Map
	//   - Chunk

	class ShadowWorld;

	//A set of maps that are loaded together
	//Like the overworld
	//Separate Levels would be the dungeons and interiors
	class LevelMap
	{
	public:
		//id
		std::string id;

		//name
		std::string name;

		//prefix to the chunk files
		std::string prefix;

		//Containing world
		ShadowWorld* world;

		//List of loaded maps
		std::list<MapChunk*> chunks;


		LevelMap(ShadowWorld* world);

		//Update
		//Here we get the map loader point(most cases the player pos) and check what maps we need
		//Than load up the maps that are not yet loaded.
		void Update(const ShadowMath::Vector2int& pos);

		//Unload a chunk
		void UnloadChunk(const ShadowMath::Vector2int& id);
		void UnloadChunk(MapChunk* chunk);

		//Load new chunks
		void LoadChunk(const ShadowMath::Vector2int& id);

		MapChunk* GetLoadedChunk(const ShadowMath::Vector2int& id);

		std::string GenerateMapName(const ShadowMath::Vector2int& id) const;
	};


	//A single World that can have many levels
	class ShadowWorld : public ShadowEngine::Assets::ShadowAsset
	{
	public:
		//Properties #####################
		std::string name;
		std::string id;

		//Active map
		LevelMap* activeMap;

		//All the maps in this World
		std::map<std::string, LevelMap*> maps;

		//World settings

		int chunkSizeX;
		int chunkSizeY;
		//What map files are in this world
		//where they are placed

		// Functions #####################

		//Update the system to check if new maps need to be loaded
		void Update(const ShadowMath::Vector2int& pos);

		void SetActiveMap(std::string name);
	};

}
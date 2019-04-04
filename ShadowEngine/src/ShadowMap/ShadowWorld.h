//
// Created by dpete on 3/6/2019.
//

#ifndef SHADOWENGINE_SHADOWWORLD_H
#define SHADOWENGINE_SHADOWWORLD_H

#include "list"
#include <map>

#include "ShadowMapChunk.h"
#include "../ShadowMath/Vector2float.h"
#include "../ShadowAsset/ShadowAsset.h"

//World
// - Map
//   - Chunk

class ShadowWorld;

//A set of maps that are loaded together
class WorldMap{
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
    std::list<ShadowMapChunk* > chunks;


    WorldMap(ShadowWorld *world);

    //Update
    //Here we get the map loader point and check what maps we need
    //Than load up the maps that are not yet loaded.
    void Update(const ShadowMath::Vector2int& pos);

    //Unload a chunk
    void UnloadChunk(const ShadowMath::Vector2int& id);
    void UnloadChunk(ShadowMapChunk* chunk);

    //Load new chunks
    void LoadChunk(const ShadowMath::Vector2int& id);

	ShadowMapChunk* GetLoadedChunk(const ShadowMath::Vector2int& id);

    std::string GenerateMapName(const ShadowMath::Vector2int& id) const;
};


//A single World that can have many maps and sizes
class ShadowWorld  : public ShadowAsset{
public:
    //Properties #####################
        std::string name;
		std::string id;

        //Active map
        WorldMap* activeMap;

        //All the maps in this World
        std::map<std::string,WorldMap*> maps;

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


#endif //SHADOWENGINE_SHADOWWORLD_H
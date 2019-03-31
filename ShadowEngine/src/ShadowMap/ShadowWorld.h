//
// Created by dpete on 3/6/2019.
//

#ifndef SHADOWENGINE_SHADOWWORLD_H
#define SHADOWENGINE_SHADOWWORLD_H

#include "list"

#include "ShadowMapChunk.h"
#include "../ShadowMath/Vector2float.h"

//World
// - Map
//   - Chunk

class ShadowWorld;

//A single chunk file
class MapChunk{
public:
    ShadowMath::Vector2int pos;
    //Name of the file
    //Reference to the object

    ShadowMapChunk* chunk;
};

//A set of maps that are loaded together
class WorldMap{
public:
    //id
    std::string id;

    //name
    std::string name;

    //prefix to the chunk files
    bool  hasPrefix;
    std::string prefix;

    //Containing world
    ShadowWorld* world;

    //List of loaded maps
    std::list<MapChunk* > chunks;


    WorldMap(ShadowWorld *world);

    //Update
    //Here we get the map loader point and check what maps we need
    //Than load up the maps that are not yet loaded.
    void Update(ShadowMath::Vector2float pos);

    //Unload a chunk
    void UnloadChunk(ShadowMath::Vector2int id);
    void UnloadChunk(MapChunk* chunk);

    //Load new chunks
    void LoadChunk(ShadowMath::Vector2int id);

    MapChunk* GetLoadedChunk(ShadowMath::Vector2int id);

    std::string GenerateMapName(ShadowMath::Vector2int id);
};


//A single World that can have many maps and sizes
class ShadowWorld {
public:
    //Properties #####################
        std::string name;

        //Active map
        WorldMap* activeMap;

        //All the maps in this World
        std::vector<WorldMap*> maps;

        //World settings

        int chunkSizeX;
        int chunkSizeY;
        //What map files are in this world
        //where they are placed

    // Functions #####################

        //Update the system to check if new maps need to be loaded
        void Update(ShadowMath::Vector2float pos);

};


#endif //SHADOWENGINE_SHADOWWORLD_H

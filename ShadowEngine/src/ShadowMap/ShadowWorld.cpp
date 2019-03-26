//
// Created by dpete on 3/6/2019.
//

#include <AssetLoader.h>
#include "ShadowWorld.h"

#include "list"
#include "string"
#include "sstream"

void ShadowWorld::Update(ShadowMath::Vector2float pos) {
    //Send the position to the active map so it can load i't chunks

}

void WorldMap::Update(ShadowMath::Vector2float pos) {
    //Load chunks if nececerry
    //xxxxx
    //xLLLx
    //xLPLx
    //xLLLx
    //xxxxx

    ShadowMath::Vector2int playerChunk;

    playerChunk.x = pos.x / this->world->chunkSizeX;
    playerChunk.y = pos.y / this->world->chunkSizeY;

    std::list<ShadowMath::Vector2int> neededChunks;

    for (int x = playerChunk.x - 1; x <= playerChunk.x + 1; x++) {
        for (int y = playerChunk.y - 1; y <= playerChunk.y; y++) {

            neededChunks.emplace_back(x,y);
        }
    }


    for (auto i : this->chunks) {
        bool needed = false;
        for (auto s : neededChunks) {
            if(i->pos == s){
                needed = true;
                neededChunks.remove(s);
            }
        }
        if(!needed){
            //Unload cause it is not needed
            UnloadChunk(i);
        }
    }

    for (auto i : neededChunks) {
        //Load the new ones
        LoadChunk(i);
    }
}

void WorldMap::UnloadChunk(MapChunk* chunk) {
    chunks.remove(chunk);

    delete chunk;
}

void WorldMap::UnloadChunk(ShadowMath::Vector2int id) {
    auto chunk = GetLoadedChunk(id);

    UnloadChunk(chunk);
}

MapChunk* WorldMap::GetLoadedChunk(ShadowMath::Vector2int id) {
    for(auto i : this->chunks)
    {
        if(i->pos == id){
            return i;
        }
    }
    return nullptr;
}

void WorldMap::LoadChunk(ShadowMath::Vector2int id) {
    std::string mapName = GenerateMapName(id);
    AssetLoader::LoadMap(mapName);
}

std::string WorldMap::GenerateMapName(ShadowMath::Vector2int id) {

    std::stringstream ss;
    if(this->hasPrefix){
        ss << this->prefix << "_" << id.x << "_" << id.y;
    }
    else {
        ss << this->world->name << "_" << this->name << "_" << id.x << "_" << id.y;
    }


    return ss.str();

}

WorldMap::WorldMap(ShadowWorld *world) : world(world) {}

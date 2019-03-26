//
// Created by dpete on 2/26/2019.
//

#ifndef SHADOWENGINE_SHADOWMAP_H
#define SHADOWENGINE_SHADOWMAP_H


#include <string>
#include <vector>
#include "../ShadowMath/Vector2int.h"
#include "../ShadowEntity/Entity.h"

class ShadowMapChunk;

class ShadowMapLayer
{
public:
    int(*data); //a row mayor flat 2d array

    std::string name;

    bool visible;

    ShadowMapChunk* map;

    ShadowMapLayer(ShadowMapChunk& m){
        this->map = &m;
    }


    void SetTile(ShadowMath::Vector2int pos, int tileID);

    int GetTile(ShadowMath::Vector2int pos);
};

class ShadowMapChunk {
public:
    std::string name;

    int height;
    int width;

    int tileHeight;
    int tileWidth;

    std::vector<ShadowMapLayer*> layers;

    std::vector<ShadowEntity::Entity*> entities;

    ShadowMapLayer& GetLayer(int id);
};


#endif //SHADOWENGINE_SHADOWMAP_H

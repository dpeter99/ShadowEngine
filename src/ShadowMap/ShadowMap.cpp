//
// Created by dpete on 2/26/2019.
//

#include "ShadowMap.h"

void ShadowMapLayer::SetTile(Vector2int pos, int tileID){
    data[(pos.y * this->map->width) + pos.x]=tileID;
}

int ShadowMapLayer::GetTile(Vector2int pos) {
    return this->data[(pos.y * this->map->width) + pos.x];
}

ShadowMapLayer& ShadowMap::GetLayer(int id) {
    return *this->layers[id];
}

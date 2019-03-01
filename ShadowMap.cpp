//
// Created by dpete on 2/26/2019.
//

#include "ShadowMap.h"

void ShadowMapLayer::SetTile(Vector2int pos, int tileID){
    data[(pos.y * this->map->width) + pos.x]=tileID;
}
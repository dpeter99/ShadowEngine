//
// Created by dpete on 2/26/2019.
//

#include "ShadowMapChunk.h"

void ShadowMapLayer::SetTile(ShadowMath::Vector2int pos, int tileID)
{
	data[(pos.y * this->map->width) + pos.x] = tileID;
}

int ShadowMapLayer::GetTile(ShadowMath::Vector2int pos)
{
	return this->data[(pos.y * this->map->width) + pos.x];
}

ShadowMapLayer& ShadowMapChunk::GetLayer(int id)
{
	return *this->layers[id];
}

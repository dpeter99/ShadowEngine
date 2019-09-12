//
// Created by dpete on 2/26/2019.
//

#include "shpch.h"

#include "ShadowMapChunk.h"

void ShadowWorld::ShadowMapLayer::SetTile(ShadowMath::Vector2int pos, int tileID)
{
	data[(pos.y * this->map->width) + pos.x] = tileID;
}

int ShadowWorld::ShadowMapLayer::GetTile(ShadowMath::Vector2int pos)
{
	return this->data[(pos.y * this->map->width) + pos.x];
}

ShadowWorld::ShadowMapLayer& ShadowWorld::ShadowMapChunk::GetLayer(int id)
{
	return *this->layers[id];
}

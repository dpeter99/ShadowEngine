//
// Created by dpete on 3/1/2019.
//
#include "shpch.h"

#include <iostream>
#include "ShadowMapRenderer.h"


void ShadowMapRenderer::RenderMap(ShadowMapChunk& map)
{
	ShadowMapLayer layer = map.GetLayer(0);

	for (int y = 0; y < map.height; ++y)
	{
		for (int x = 0; x < map.width; ++x)
		{
			std::cout << layer.GetTile(ShadowMath::Vector2int(x, y)) << ' ';
		}
		std::cout << "\n";
	}

	for (auto i : map.entities)
	{
		i->Render();
	}
}

#include "shpch.h"

#include "ShadowWorld.h"


#include "ShadowAsset/AssetManager.h"

namespace ShadowEngine::World {

	void ShadowWorld::Update(const ShadowMath::Vector2int& pos)
	{
		//Send the position to the active map so it can load i't chunks
		if (this->activeMap != nullptr)
		{
			this->activeMap->Update(pos);
		}
	}

	void ShadowWorld::SetActiveMap(std::string name)
	{
		auto m = this->maps.find(name);
		if (m != this->maps.end())
		{
			this->activeMap = m->second;
		}
	}

	void LevelMap::Update(const ShadowMath::Vector2int& pos)
	{
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

		for (int x = playerChunk.x - 1; x <= playerChunk.x + 1; x++)
		{
			for (int y = playerChunk.y - 1; y <= playerChunk.y + 1; y++)
			{
				neededChunks.emplace_back(x, y);
			}
		}


		for (auto i : this->chunks)
		{
			bool needed = false;
			for (ShadowMath::Vector2int s : neededChunks)
			{
				if (i->pos == s)
				{
					needed = true;
					//TODO:This part causes errors, probalby because destructing the sample
					//neededChunks.remove(s);
				}
			}
			if (!needed)
			{
				//Unload cause it is not needed
				UnloadChunk(i);
			}
		}

		for (auto i : neededChunks)
		{
			//Load the new ones
			LoadChunk(i);
		}
	}

	void LevelMap::UnloadChunk(World::MapChunk* chunk)
	{
		chunks.remove(chunk);

		delete chunk;
	}

	void LevelMap::UnloadChunk(const ShadowMath::Vector2int& id)
	{
		auto chunk = GetLoadedChunk(id);

		UnloadChunk(chunk);
	}

	MapChunk* LevelMap::GetLoadedChunk(const ShadowMath::Vector2int& id)
	{
		for (auto i : this->chunks)
		{
			if (i->pos == id)
			{
				return i;
			}
		}
		return nullptr;
	}

	void LevelMap::LoadChunk(const ShadowMath::Vector2int& id)
	{
		std::string mapName = GenerateMapName(id);
		auto c = Assets::AssetManager::GetAsset_OLD<MapChunk>(mapName);
		if (c == nullptr)
			return;

		this->chunks.emplace_back(c);

		//AssetLoader::LoadMap(mapName);
	}

	std::string LevelMap::GenerateMapName(const ShadowMath::Vector2int& id) const
	{
		std::stringstream ss;

		ss << "Resources/Worlds/" << this->world->id << "/" << this->world->id << "-" << this->id << "_"
			<< (id.x < 0 ? "-" : "") << std::setw(3) << std::setfill('0') << std::internal << abs(id.x) << "_"
			<< (id.x < 0 ? "-" : "") << std::setw(3) << std::setfill('0') << std::internal << abs(id.y);

		return ss.str();
	}

	LevelMap::LevelMap(ShadowWorld* world) : world(world)
	{
	}

}
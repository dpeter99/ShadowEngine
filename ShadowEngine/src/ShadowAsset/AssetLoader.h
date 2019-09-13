#pragma once


#include <map>
#include "list"
#include "ShadowMap/ShadowMapChunk.h"
#include "ShadowMap/ShadowWorld.h"

namespace ShadowEngine::Assets {

	class Element
	{
	public:
		Element* parent;

		std::string name;

		bool isBlock;

		std::string value;

		std::list<Element*> properties_old;
		std::map<std::string, Element*> properties;

		std::string GetStringProperty(std::string name);

		~Element();
	};

	class AssetLoader
	{
		static Element* LoadFile(std::string name);

	public:
		static World::MapChunk* LoadMap(std::string name);

		static World::ShadowWorld* LoadWorld(std::string name);

		template <class T>
		static T* LoadAsset(std::string name);
	};
}
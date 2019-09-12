#include <map>
#include "list"
#include "ShadowMap/ShadowMapChunk.h"
#include "ShadowMap/ShadowWorld.h"

namespace ShadowAssets {

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
		static ShadowWorld::ShadowMapChunk* LoadMap(std::string name);

		static ShadowWorld::ShadowWorld* LoadWorld(std::string name);

		template <class T>
		static T* LoadAsset(std::string name);
	};
}
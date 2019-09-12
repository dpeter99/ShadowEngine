#include <string>
#include <vector>
#include "../ShadowMath/Vector2int.h"
#include "../ShadowEntity/Entity.h"
#include "../ShadowMath/Vector2int.h"
#include "ShadowAsset/ShadowAsset.h"

namespace ShadowWorld {

	class ShadowMapChunk;

	class ShadowMapLayer
	{
	public:
		int(*data); //a row mayor flat 2d array

		std::string name;

		bool visible;

		ShadowMapChunk* map;

		ShadowMapLayer(ShadowMapChunk& m, bool visible, int* data)
		{
			this->map = &m;
			this->visible = visible;
			this->data = data;
		}


		void SetTile(ShadowMath::Vector2int pos, int tileID);

		int GetTile(ShadowMath::Vector2int pos);
	};

	class ShadowMapChunk : public ShadowAsset
	{
	public:
		std::string name;

		//the position where this map should be drawn
		ShadowMath::Vector2int pos;

		int height;
		int width;

		int tileHeight;
		int tileWidth;

		std::vector<ShadowMapLayer*> layers;

		std::vector<ShadowEntity::Entity*> entities;

		ShadowMapLayer& GetLayer(int id);
	};

}
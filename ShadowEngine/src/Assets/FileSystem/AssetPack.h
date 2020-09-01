#pragma once

#include <string>

namespace ShadowEngine::Assets::FileSystem {

	class AssetPack {

		std::string packName;
		std::string packID;
		std::string packPath;

	public:

		AssetPack(std::string name, std::string id, std::string path):
			packName(name),
			packID(id),
			packPath(path)
		{

		}

		const std::string& GetPath() {
			return packPath;
		}

		const std::string& GetName() {
			return packName;
		}

		const std::string& GetID() {
			return packID;
		}

	};

}
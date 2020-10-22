#include "shpch.h"

#include "ShadowAsset.h"

namespace ShadowEngine::Assets {

	void ShadowAsset::SetName(std::string s) 
	{
		name = s;
	}

	void ShadowAsset::Load(SFF::SFFElement& root, FileSystem::Path path)
	{
		this->path = path;
	}

}

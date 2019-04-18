#pragma once

#include <string>

class ShadowAsset
{
public:
	int runtimeAssetID;
	std::string path;


	ShadowAsset();
	virtual ~ShadowAsset();
};

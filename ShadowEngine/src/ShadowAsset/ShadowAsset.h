#pragma once
#include <string>

#include "Core/Core.h"
#include "ShadowFileFormat/SFFElement.h"



namespace ShadowEngine::Assets {

	class Element;
	
	class ShadowAsset : public ShadowEngine::SHObject
	{
		SHObject_Base(ShadowAsset)
		
	public:
		/// <summary>
		/// ID of this instance
		/// </summary>
		int runtimeAssetID;
		
		/// <summary>
		/// Path it was loaded from
		/// </summary>
		std::string path;

		virtual void Load(SFF::SFFElement& root) = 0;
	};
}

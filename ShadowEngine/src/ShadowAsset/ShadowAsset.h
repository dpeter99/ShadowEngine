#pragma once
#include "Core/Core.h"
#include <string>



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

		virtual void Load(ShadowEngine::Assets::Element& root) = 0;
	};
}

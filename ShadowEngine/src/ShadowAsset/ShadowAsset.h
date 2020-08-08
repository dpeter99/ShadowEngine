#pragma once
#include "Core/Core.h"
#include <string>



namespace ShadowEngine::Assets {

	class Element;
	
	class ShadowAsset : public ShadowEngine::SHObject
	{
		SHObject_Base(ShadowAsset)
		
	public:
		/**
		 * \brief ID of this instance
		 */
		int runtimeAssetID;
		/**
		 * \brief Path it was loaded from
		 */
		std::string path;

		void Load(ShadowEngine::Assets::Element& root) {};
	};
}

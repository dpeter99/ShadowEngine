#pragma once
#include "SFFElement.h"

namespace ShadowEngine::SFF {

	class SFFParser
	{
	public:
		static SFFElement* ReadFromStream(std::istream& stream);

		static SFFElement* ReadFromFile(std::string path);
	};

}

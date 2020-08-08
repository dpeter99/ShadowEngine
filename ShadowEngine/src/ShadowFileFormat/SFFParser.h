#pragma once
#include "SFFElement.h"
#include "SFFVersion.h"

namespace ShadowEngine::SFF {

	class SFFParser
	{
	public:
		static SFFElement* ReadFromStream(std::istream& stream);

		static SFFVersion ReadVersionFromHeader(std::istream& stream);

		static SFFElement* ReadFromFile(std::string path);
	};

}

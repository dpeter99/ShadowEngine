#pragma once

#include "Core/Core.h"
#include <string>

namespace ShadowEngine::Assets::FileSystem {

	const char pack_delimiter = ':';

	class Path {
		std::string pack;
		std::string path;

	public:

		Path(std::string p)
		{
			auto delim = p.find(pack_delimiter);

			this->pack = p.substr(0, delim);
			SH_CORE_ASSERT(!pack.empty(), "Couldn't find the pack name in string: '{0}'", p);
			
			this->path = p.substr(delim + 1);
		
		}

		Path(std::string pack, std::string path): pack(pack), path(path)
		{
			
		}

		std::string GetFullPath() const;

		std::string GetPath() const {
			return pack + ":" + path;
		}

		bool operator==(const Path& other) const {
			return other.pack == pack && other.path == path;
		}

		operator std::string() const{
			return pack + ":" + path;
		}

	};
}
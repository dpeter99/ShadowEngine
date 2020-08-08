#include "shpch.h"
#include "SFFParser.h"


namespace ShadowEngine::SFF {

	SFFElement* SFFParser::ReadFromStream(std::istream& stream)
	{
		auto version = ReadVersionFromHeader(stream);
		if (version.invalid) {
			SH_CORE_WARN("Shadow File is invalid");
			return nullptr;
		}


		//The current node that we are building
		auto* context = new SFFElement;

		//Top level Element
		SFFElement* base = context;

		//The new node that will be a child of the context
		auto* current = new SFFElement;




		std::string buffer;

		char c;
		while (!stream.eof())
		{
			stream.get(c);
			if (c == ':')
			{
				//The stuff in the buffer is a parameter name
				std::cout << "Name: " << buffer;
				current->name = buffer;
				buffer = "";
			}
			else if (c == '{')
			{
				//Start of a new block
				current->isBlock = true;
				current->parent = context;
				context->children[current->name] = current;
				context = current;

				current = new SFFElement;
			}
			else if (c == ',')
			{
				// End of a property
				//The stuff is the value
				std::cout << "Value: " << buffer << std::endl;
				current->value = buffer;
				current->parent = context;
				current->isBlock = false;
				buffer = "";

				context->children[current->name] = current;

				current = new SFFElement();
			}
			else if (c == '}')
			{
				// End of a block
				context = context->parent;
			}
			else
			{
				if (std::isspace(c) == 0)
				{
					buffer += c;
				}
			}
		}

		std::cout << "END" << std::endl;

		return base;
	}

	SFFVersion SFFParser::ReadVersionFromHeader(std::istream& stream) {
		std::string line;
		std::getline(stream, line);
		auto parts = explode(line, '_');
		if (parts[0] != "ShadowFileFormat") {
			return SFFVersion(-1,-1,-1);
		}
		else {
			int mayor = std::stoi(parts[1]);
			int minor = std::stoi(parts[2]);
			int patch = std::stoi(parts[3]);
			return SFFVersion(mayor, minor, patch);
		}
		
	}



	SFFElement* SFFParser::ReadFromFile(std::string path)
	{
		std::ifstream inputFileStream(path);

		if (errno)
		{
			SH_CORE_ERROR("Error: {0} | File: {1}", strerror(errno), path);
			//std::cerr << "Error: " << strerror(errno) << std::endl;
			//std::cerr << "File: " << path << std::endl;
			return nullptr;
		}

		return ReadFromStream(inputFileStream);
	}

}
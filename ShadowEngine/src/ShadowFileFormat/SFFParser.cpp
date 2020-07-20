#include "shpch.h"
#include "SFFParser.h"

namespace ShadowEngine::SFF {

	SFFElement* SFFParser::ReadFromStream(std::istream& stream)
	{
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
				context->properties[current->name] = current;
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

				context->properties[current->name] = current;

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
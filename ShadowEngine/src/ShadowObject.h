#pragma once
#include <string>

class ShadowObject
{
	static std::string typeID;
public:

	template<class T>
	bool TypeIs()
	{
		if(typeID == T.typeID)
		{
			return true;
		}
		return false;
	}

	ShadowObject();
	~ShadowObject();
};


#pragma once
#include <hstring.h>


template <typename OutType, typename InType>
bool is[[depricated]](InType& data, OutType** out)
{
	if(data.GetType() == OutType::Type())
	{
		*out = dynamic_cast<OutType*>(&data);
		return true;
	}
	return false;
}


template<class T>
inline float convert(T value);


inline float convert(bool value)
{
	return value ? 1 : 0;
}

inline float convert(float value)
{
	return value;
}

inline std::wstring s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}


inline const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}
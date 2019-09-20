#pragma once

/*
template <typename CheckType, typename DataType>
bool is(DataType& data, CheckType** out)
{
	if (&data == nullptr) return false;


	*out = dynamic_cast<CheckType*>(&data);
	return *out == nullptr ? false : true;
}
*/

template <typename OutType, typename InType>
bool is(InType& data, OutType** out)
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
	return value ? 1.0f : 0.0f;
}

inline float convert(float value)
{
	return value;
}
#pragma once

template <typename CheckType, typename DataType>
bool is(DataType& data, CheckType** out)
{
	if (&data == nullptr) return false;


	*out = dynamic_cast<CheckType*>(&data);
	return *out == nullptr ? false : true;
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
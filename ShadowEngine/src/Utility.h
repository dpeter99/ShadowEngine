#pragma once

template <typename CheckType, typename DataType>
bool is(DataType& data, CheckType** out)
{
	if (&data == nullptr) return false;


	*out = dynamic_cast<CheckType*>(&data);
	return *out == nullptr ? false : true;
}

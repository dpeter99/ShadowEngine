#pragma once

template< typename Type, typename DataType >
bool is(DataType& data, Type** out) {
	if (&data == nullptr) return false;
	*out = dynamic_cast<Type*>(&data);
	return *out == nullptr ? false : true;
}
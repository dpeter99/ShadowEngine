#pragma once

template< typename Type, typename DataType >
bool is(const DataType& data) {
	if (&data == NULL) return false;
	return typeid(data) == typeid(Type);
}
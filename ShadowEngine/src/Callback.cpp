#include "shpch.h"

#include "Callback.h"


void Callback::operator()()
{
	for (auto callback : callbacks)
	{
		callback();
	}
}

void Callback::operator+=(std::function<void()> fn)
{
	callbacks.push_back(fn);
}

Callback::Callback()
{
}


Callback::~Callback()
{
}

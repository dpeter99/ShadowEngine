#pragma once
#include <vector>
#include <functional>

class Callback
{

	std::vector<std::function<void()>> callbacks;

public:

	void operator()();
	void operator+=(std::function<void()> fn);


	Callback();
	~Callback();
};


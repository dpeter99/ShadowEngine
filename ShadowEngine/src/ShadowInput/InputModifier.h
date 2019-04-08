#pragma once
class InputModifier
{

public:
	InputModifier();
	~InputModifier();

	virtual void ProcessInput() = 0;
};


#pragma once

namespace ShadowEngine
{

	class IGame
	{
	public:
		virtual void Init() = 0;

		virtual void Start() = 0;

		//virtual void Loop() = 0;

		virtual void Stop() = 0;
		
	};

}
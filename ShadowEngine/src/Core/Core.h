#pragma once

#include <memory>


#define BIT(x) (1 << x)

#ifdef SH_ENABLE_ASSERTS
	#define SH_ASSERT(x, ...) { if(!(x)) { SH_ERROR(__VA_ARGS__); __debugbreak(); } }
	
	#define SH_CORE_ASSERT(x, ...) { if(!(x)) { SH_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
	
#else
	#define SH_ASSERT(x, ...)
	#define SH_CORE_ASSERT(x, ...)
#endif

namespace ShadowEngine {
	class IGame;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;


	typedef IGame* (*SetupFunction)();
	
}

extern ShadowEngine::SetupFunction _setupFunc;
#pragma once

#include <memory>

#include "Log.h"

#define BIT(x) (1 << x)

#ifdef SH_ENABLE_ASSERTS

	/// <summary>
	/// Breaks if the test fails
	/// </summary>
	/// <param name="x"></param>
	#define SH_ASSERT(x, ...) { if(!(x)) { SH_ERROR(__VA_ARGS__); __debugbreak(); } }
	
	#define SH_CORE_ASSERT(x, ...) { if(!(x)) { SH_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
	
#else
	#define SH_ASSERT(x, ...)
	#define SH_CORE_ASSERT(x, ...)
#endif


#define _KB(x) (x * 1024)
#define _MB(x) (x * 1024 * 1024)

#define _64KB _KB(64)
#define _1MB _MB(1)
#define _2MB _MB(2)
#define _4MB _MB(4)
#define _8MB _MB(8)
#define _16MB _MB(16)
#define _32MB _MB(32)
#define _64MB _MB(64)
#define _128MB _MB(128)
#define _256MB _MB(256)

// The min/max macros conflict with like-named member functions.
// Only use std::min and std::max defined in <algorithm>.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
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
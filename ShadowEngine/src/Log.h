#pragma once

#include "ShadowModules/ShadowModule.h"
#include "Core/Core.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)


namespace ShadowEngine {

	class Log : public ShadowModule
	{
		SHObject_Base(Log)

	public:
		void PreInit() override;
		void Init() override;
		void Update() override {};
		void LateRender() override {};
		void Render() override {};
		std::string GetName() override { return "Log"; }

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define SH_CORE_TRACE(...)    ::ShadowEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SH_CORE_INFO(...)     ::ShadowEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SH_CORE_WARN(...)     ::ShadowEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SH_CORE_ERROR(...)    ::ShadowEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SH_CORE_CRITICAL(...) ::ShadowEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SH_TRACE(...)         ::ShadowEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SH_INFO(...)          ::ShadowEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define SH_WARN(...)          ::ShadowEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SH_ERROR(...)         ::ShadowEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define SH_CRITICAL(...)      ::ShadowEngine::Log::GetClientLogger()->critical(__VA_ARGS__)

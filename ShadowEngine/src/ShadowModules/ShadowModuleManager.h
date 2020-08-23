#pragma once
#include <list>

#include "Log.h"
#include "ShadowModule.h"
#include "Core/Core.h"


namespace ShadowEngine {
	class ShadowModuleManager
	{
	public:
		static ShadowModuleManager* instance;

		std::list<Scope<ShadowModule>> modules;

		ShadowModuleManager();
		~ShadowModuleManager();

		void PushModule(ShadowModule* module);

		ShadowModule& GetModule(std::string name);

		template<typename T>
		T* GetModuleByType()
		{
			for (auto& module : modules)
			{
				if (module->GetTypeId() == T::TypeId())
					return dynamic_cast<T*>(module.get());
			}
			SH_CORE_ERROR("Can't find the module {0}", T::Type());
			return nullptr;
		}

		void Init();
		void Update();
		void LateRender();
		void Render();
		void AfterFrameEnd();
	};
}

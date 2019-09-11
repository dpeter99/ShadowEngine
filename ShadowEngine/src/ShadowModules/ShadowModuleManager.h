#pragma once
#include <list>
#include "ShadowModule.h"



class ShadowModuleManager
{
public:
	static ShadowModuleManager* instance;

	std::list<ShadowModule*> modules;

	ShadowModuleManager();
	~ShadowModuleManager();

	void PushModule(ShadowModule* module);

	ShadowModule& GetModule(std::string name);

	template<typename T>
	T& GetModuleByType()
	{
		for (auto module : modules)
		{
			if (module->GetTypeId() == T::TypeId())
				return *static_cast<T*>(module);
		}
		SH_ASSERT(false, "Can't find the module");
		//return NULL;
	}

	void Init();
	void Update();
	void LateRender();
	void Render();
};

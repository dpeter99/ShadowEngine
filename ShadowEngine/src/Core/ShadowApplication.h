#pragma once
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowAsset/AssetManager.h"
#include "ShadowWindow.h"

namespace ShadowEngine {

	class ShadowApplication
	{
		static ShadowApplication* instance;

		ShadowWindow* window_;

		ShadowEngine::ShadowModuleManager moduleManager;

		//AssetManager asset;

		bool running = true;

	public:
		ShadowApplication();
		virtual ~ShadowApplication();

		static ShadowApplication& Get() { return *instance; };

		ShadowWindow& GetWindow() const { return *window_; };
		void SetWindow(ShadowWindow* w) { window_ = w; }

		ShadowEngine::ShadowModuleManager& GetModuleManager() { return moduleManager; };

		void Init();
		void Start();
	};
}
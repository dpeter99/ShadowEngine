#pragma once
#include "ShadowModules/ShadowModuleManager.h"
#include "ShadowAsset/AssetManager.h"
#include "ShadowWindow.h"

namespace ShadowEngine {

	/// <summary>
	/// Represents the application
	/// </summary>
	class ShadowApplication
	{
		/// <summary>
		/// This is the singleton instance
		/// </summary>
		static ShadowApplication* instance;


		/// <summary>
		/// The active window that we are drawing to
		/// </summary>
		ShadowWindow* window_;

		/// <summary>
		/// The module manager instance
		/// </summary>
		ShadowEngine::ShadowModuleManager moduleManager;

		//AssetManager asset;

		/// <summary>
		/// Represents the running state.
		/// </summary>
		/// If set to false the main loop will stop and continue with the shutdown.
		bool running = true;

	public:
		/// <summary>
		/// Default constructor
		/// </summary>
		ShadowApplication();
		virtual ~ShadowApplication();

		/// <summary>
		/// Static getter for the singleton instance 
		/// </summary>
		/// Use this for accessing the Application
		/// <returns>The current application reference</returns>
		static ShadowApplication& Get() { return *instance; };

		/// <summary>
		/// Returns the active window used for rendering
		/// </summary>
		/// <returns> The window instance </returns>
		ShadowWindow& GetWindow() const { return *window_; };
		void SetWindow(ShadowWindow* w) { window_ = w; }

		ShadowEngine::ShadowModuleManager& GetModuleManager() { return moduleManager; };

		void Init();
		void Start();
	};
}
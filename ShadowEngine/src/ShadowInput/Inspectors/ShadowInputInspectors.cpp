#include "shpch.h"
#include "ShadowInput/ShadowActionSystem.h"
#include "Core/ShadowApplication.h"
#include "Debug/Debug.h"
#include "InputActionInspector.h"
#include "Inspector/InspectorSystem.h"
#include "ShadowInput/Bindings/KeyboardBinding.h"
#include "KeyboardBindingInspector.h"
#include "ShadowInput/Modifiers/ModifierHold.h"
#include "ModifierHoldInspector.h"
#include "ShadowInput/Bindings/Binding2D.h"
#include "ShadowInput/Bindings/Binding1D.h"
#include "Binding1DInspector.h"
#include "Binding2DInspector.h"
#include "ShadowInput/Bindings/BindingAND.h"
#include "BindingANDInspector.h"
#include "BindingORInspector.h"

namespace  ShadowEngine::InputSystem {

	void ShadowActionSystem::RegisterInspectors()
	{
		//auto debug = dynamic_cast<Debug&>(ShadowApplication::Get().GetModuleManager().GetModule("Debug"));

		Debug::InspectorSystem::AddInspector(ShadowAction<bool>::Type(), new InputActionInspector());
		Debug::InspectorSystem::AddInspector(ShadowAction<float>::Type(), new InputActionInspector());
		Debug::InspectorSystem::AddInspector(ShadowAction<ShadowMath::Vector2float>::Type(), new InputActionInspector());

		Debug::InspectorSystem::AddInspector(KeyboardBinding::Type(), new KeyboardBindingInspector());
		Debug::InspectorSystem::AddInspector(ModifierHold::Type(), new ModifierHoldInspector());

		Debug::InspectorSystem::AddInspector(Binding1D<bool>::Type(), new Binding1DInspector());
		Debug::InspectorSystem::AddInspector(Binding1D<float>::Type(), new Binding1DInspector());

		Debug::InspectorSystem::AddInspector(Binding2D<ShadowMath::Vector2float>::Type(), new Binding2DInspector());

		Debug::InspectorSystem::AddInspector(BindingAND<bool>::Type(), new BindingANDInspector());

		Debug::InspectorSystem::AddInspector(BindingOR<bool>::Type(), new BindingORInspector());
	}

}
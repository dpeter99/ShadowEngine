#include "shpch.h"
#include "ShadowInput/ShadowActionSystem.h"
#include "ShadowApplication.h"
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

void ShadowInput::ShadowActionSystem::RegisterInspectors()
{
	//auto debug = dynamic_cast<Debug&>(ShadowApplication::Get().GetModuleManager().GetModule("Debug"));

	InspectorSystem::AddInspector(ShadowAction<bool>::Type(), new InputActionInspector());
	InspectorSystem::AddInspector(ShadowAction<float>::Type(), new InputActionInspector());
	InspectorSystem::AddInspector(ShadowAction<ShadowMath::Vector2float>::Type(), new InputActionInspector());

	InspectorSystem::AddInspector(KeyboardBinding::Type(), new KeyboardBindingInspector());
	InspectorSystem::AddInspector(ModifierHold::Type(), new ModifierHoldInspector());

	InspectorSystem::AddInspector(Binding1D<bool>::Type(), new Binding1DInspector());
	InspectorSystem::AddInspector(Binding1D<float>::Type(), new Binding1DInspector());

	InspectorSystem::AddInspector(Binding2D<ShadowMath::Vector2float>::Type(), new Binding2DInspector());

	InspectorSystem::AddInspector(BindingAND<bool>::Type(), new BindingANDInspector());

	InspectorSystem::AddInspector(BindingOR<bool>::Type(), new BindingORInspector());
}


#include "Binding1D.h"

namespace  ShadowInput {
	void Binding1D::ProcessEvent(const ShadowEvent& event)
	{
	}

	Binding1D::Binding1D(InputBinding<bool>* _xpositive, InputBinding<bool>* _xnegative): pos(_xpositive), neg(_xnegative)
	{
	}

	Binding1D::~Binding1D()
	{
	}
}

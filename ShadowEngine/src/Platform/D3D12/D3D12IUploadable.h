#pragma once

#include "CommandList.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12IUploadable {

	public:
		virtual void RecordTransfer(Ref<D3D12::CommandList> cmd) = 0;

		virtual void FinishedUploading() = 0;
	};

}
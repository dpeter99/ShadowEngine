#pragma once

#include "D3D12CommandList.h"

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12IUploadable {

	public:
		virtual void RecordTransfer(Ref<D3D12::D3D12CommandList> cmd) = 0;

		virtual void FinishedUploading() = 0;
	};

}
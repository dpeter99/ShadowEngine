#include <shpch.h>

#include "Buffer.h"

namespace ShadowEngine::Rendering::D3D12 {

	Buffer::Buffer(const std::wstring& name)
		: Resource(name)
	{}

	Buffer::Buffer(const D3D12_RESOURCE_DESC& resDesc,
		size_t numElements, size_t elementSize,
		const std::wstring& name)
		: Resource(resDesc, nullptr, name)
	{}

}
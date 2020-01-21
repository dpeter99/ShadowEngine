#include "shpch.h"
#include "ConstantBuffer.h"
#include "RendererAPI.h"
#include "Platform/D3D12/D3D12ConstantBuffer.h"
#include "Renderer.h"

namespace ShadowEngine::Rendering {

	ConstantBufferImpl* ConstantBufferImpl::Create(size_t size, std::wstring debug_name)
	{
		switch (ShadowEngine::Rendering::Renderer::GetAPI())
		{
		case RendererAPI::API::None: SH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::D3D12: return (ConstantBufferImpl*) new ShadowEngine::Rendering::D3D12::DX12ConstantBuffer(size, debug_name);
		}

		SH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	ConstantBuffer_ShaderPropertySheet::
		ConstantBuffer_ShaderPropertySheet(Ref<ShaderPropertySheet> propertySheet) : ConstantBuffer(propertySheet->GetSize(), s2ws("PropertySheedData"))
	{
		data = propertySheet;
		size = propertySheet->GetSize();
	}

	void ConstantBuffer_ShaderPropertySheet::Upload()
	{
		impl->Upload(data->GetDataStruct(), size);
	}

	void ConstantBuffer_ShaderPropertySheet::Set(void* d)
	{
		
	}
}

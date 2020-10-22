#include "shpch.h"
#include "DX12IndexBuffer.h"

#include "Platform/D3D12/DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

    DX12IndexBuffer::DX12IndexBuffer(const std::wstring& name) : IndexBuffer(), Buffer(name) {

    }

    DX12IndexBuffer::DX12IndexBuffer(std::vector<uint32_t> verts, const std::wstring& name)
        : IndexBuffer(), Buffer(name),
        indices(verts)
    {
        D3D12::DX12RendererAPI::Get().UploadResource(this);
    }


    void DX12IndexBuffer::RecordTransfer(Ref<D3D12::CommandList> cmd)
    {
        cmd->CopyIndexBuffer(*this, indices);
    }

    void DX12IndexBuffer::FinishedUploading()
    {
    }

    D3D12_CPU_DESCRIPTOR_HANDLE DX12IndexBuffer::GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const
    {
        return D3D12_CPU_DESCRIPTOR_HANDLE();
    }

    D3D12_CPU_DESCRIPTOR_HANDLE DX12IndexBuffer::GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const
    {
        return D3D12_CPU_DESCRIPTOR_HANDLE();
    }

    void DX12IndexBuffer::CreateViews(size_t numElements, size_t elementSize)
    {
    }

    D3D12_CPU_DESCRIPTOR_HANDLE DX12IndexBuffer::GetConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const
    {
        return D3D12_CPU_DESCRIPTOR_HANDLE();
    }
    uint32_t DX12IndexBuffer::GetCount() const
    {
        return uint32_t();
    }

    void DX12IndexBuffer::SetName(std::string name)
    {
        Resource::SetName(s2ws(name));
    }
}
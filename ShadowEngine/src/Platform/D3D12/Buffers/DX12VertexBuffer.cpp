#include "shpch.h"
#include "DX12VertexBuffer.h"

#include "Platform/D3D12/DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

    DX12VertexBuffer::DX12VertexBuffer(const std::wstring& name) : VertexBuffer(0), Buffer(name){

    }

    DX12VertexBuffer::DX12VertexBuffer(std::vector<Vertex> verts, const std::wstring& name) 
        : VertexBuffer(0), Buffer(name),
        vertices(verts)
    {
        D3D12::DX12RendererAPI::Get().UploadResource(this);
    }


    void ShadowEngine::Rendering::D3D12::DX12VertexBuffer::RecordTransfer(Ref<D3D12::CommandList> cmd)
    {
        cmd->CopyVertexBuffer(*this, vertices);
        

    }

    void ShadowEngine::Rendering::D3D12::DX12VertexBuffer::FinishedUploading()
    {
    }

    D3D12_CPU_DESCRIPTOR_HANDLE ShadowEngine::Rendering::D3D12::DX12VertexBuffer::GetShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc) const
    {
        return D3D12_CPU_DESCRIPTOR_HANDLE();
    }

    D3D12_CPU_DESCRIPTOR_HANDLE ShadowEngine::Rendering::D3D12::DX12VertexBuffer::GetUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc) const
    {
        return D3D12_CPU_DESCRIPTOR_HANDLE();
    }

    void ShadowEngine::Rendering::D3D12::DX12VertexBuffer::CreateViews(size_t numElements, size_t elementSize)
    {
    }

    D3D12_CPU_DESCRIPTOR_HANDLE ShadowEngine::Rendering::D3D12::DX12VertexBuffer::GetConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC* srvDesc) const
    {
        return D3D12_CPU_DESCRIPTOR_HANDLE();
    }
    void DX12VertexBuffer::SetName(std::string name)
    {
        Resource::SetName(s2ws(name));
    }
}
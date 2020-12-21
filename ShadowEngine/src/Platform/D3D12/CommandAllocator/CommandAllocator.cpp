#include "shpch.h"
#include "CommandAllocator.h"

#include "Platform/D3D12/Resource/Resource.h"

namespace ShadowEngine::Rendering::D3D12 {

	CommandAllocator::CommandAllocator(com_ptr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type) :
	m_commandAllocator(commandAllocator), type(type)
	{
		static int nextID = 0;
		id = nextID++;

		m_UploadBuffer = std::make_unique<UploadBuffer>();
		m_ResourceStateTracker = std::make_unique<ResourceStateTracker>();
	}

	void CommandAllocator::SetName(std::wstring name)
	{
		this->m_commandAllocator->SetName(name.c_str());
	}

	void CommandAllocator::MarkUsed(int frame, Ref<D3D12CommandQueue> queue)
	{
		this->free = false;
		this->freeFrame = frame;
		this->freeCommandQueue = queue;
	}

	void CommandAllocator::SetFree()
	{
		this->freeFrame = -1;
		this->free = true;

		this->m_commandAllocator->Reset();
		this->m_UploadBuffer->Reset();
	}

	void CommandAllocator::TrackResource(Microsoft::WRL::ComPtr<ID3D12Object> object)
	{
		m_TrackedObjects.push_back(object);
	}

	void CommandAllocator::TrackResource(const Resource& res)
	{
		TrackResource(res.GetD3D12Resource());
	}

	void CommandAllocator::TrackObject(Microsoft::WRL::ComPtr<ID3D12Object> object)
	{
		m_TrackedObjects.push_back(object);
	}

	D3D12_COMMAND_LIST_TYPE CommandAllocator::GetType()
	{
		return this->type;
	}

	bool CommandAllocator::CheckFinished(int frame, Ref<D3D12CommandQueue> queue)
	{

		return frame >= freeFrame && queue == freeCommandQueue;
	}

}

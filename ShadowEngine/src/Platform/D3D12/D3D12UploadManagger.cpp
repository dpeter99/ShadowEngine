#include "shpch.h"

#include "D3D12UploadManagger.h"
#include "DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {
	D3D12UploadManagger::D3D12UploadManagger()
	{
		command_queue = std::make_shared<D3D12CommandQueue>(D3D12_COMMAND_LIST_TYPE_COPY);

		fence = std::make_unique<D3D12::D3D12Fence>();

		uploadQueues.push_back(std::make_shared<UploadQueue>());
		active = uploadQueues[0];

		index = 0;
	}
	void D3D12UploadManagger::Upload(Ref<D3D12IUploadable> data)
	{
		active->Upload(data);
	}

	void D3D12UploadManagger::StartUpload()
	{
		if (active->dirty) {
			index++;
			active->Execute(command_queue, index);
			command_queue->Signal(fence, index);

			Ref<UploadQueue> new_active;
			for (size_t i = 0; i < uploadQueues.size(); i++)
			{
				if (uploadQueues[i]->dirty == false &&
					uploadQueues[i]->finished == true) {
					new_active = uploadQueues[i];
				}
			}
			if (new_active == nullptr) {
				uploadQueues.push_back(std::make_shared<UploadQueue>());
				new_active = uploadQueues[uploadQueues.size()-1];
			}
			active = new_active;
		}
	}

	void D3D12UploadManagger::CheckForFnishedUploads()
	{
		unsigned long long i = fence->GetCompletedValue();

		for each (auto& e in uploadQueues)
		{
			if(!e->finished)
			e->Check(i);
		}
	}

	UploadQueue::UploadQueue()
	{
		command_list = std::make_shared<CommandList>(D3D12_COMMAND_LIST_TYPE_COPY);

		fenceValue = -1;

		dirty = false;
		
		finished = true;
	}

	void UploadQueue::Upload(Ref<D3D12IUploadable> data)
	{
		stuff.push_back(data);

		if(!command_list->IsRecording())
		command_list->Reset();

		data->RecordTransfer(this->command_list);

		dirty = true;
	}

	void UploadQueue::Execute(Ref<D3D12CommandQueue> queue, unsigned long long index) {
		command_list->Close();

		queue->Execute(command_list);

		fenceValue = index;
		finished = false;
	}

	void UploadQueue::Check(unsigned long long fv)
	{
		if (fv >= fenceValue) {
			//Upload finished
			for each (auto& item in stuff)
			{
				item->FinishedUploading();
			}
		}
	}


}
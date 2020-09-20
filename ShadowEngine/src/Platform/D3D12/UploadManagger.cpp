#include "shpch.h"

#include "UploadManagger.h"
#include "DX12RendererAPI.h"

namespace ShadowEngine::Rendering::D3D12 {

	//####################################
	//      UploadManagger
	//####################################
	
	UploadManagger::UploadManagger()
	{
		command_queue = std::make_shared<D3D12CommandQueue>(D3D12_COMMAND_LIST_TYPE_COPY);

		command_queue->SetName(L"UploadManager_Queue");
		
		uploadQueues.push_back(std::make_shared<UploadQueue>());
		active = uploadQueues[0];
		active->Open(command_queue->GetNextSignalValue(), command_queue);

		index = 0;
	}
	void UploadManagger::Upload(Ref<D3D12IUploadable> data)
	{
		active->Upload(data);
	}

	void UploadManagger::SubmitUploads()
	{
		if (active->dirty) {
			index = command_queue->GetNextSignalValue();
			active->Execute(command_queue, index);
			index = command_queue->Signal();

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
			active->Open(command_queue->GetNextSignalValue(), command_queue);
		}
	}

	void UploadManagger::CheckForFnishedUploads()
	{
		unsigned long long i = command_queue->GetCompletedValue();

		for each (auto& e in uploadQueues)
		{
			if(!e->finished)
			e->Check(i);
		}
	}

	//####################################
	//      UploadQueue
	//####################################

	std::wstring MakeName()
	{
		static int id = 0;
		std::wstring name = L"UploadQueue_";
		name += std::to_wstring(id++);
		return name;
	}
	
	UploadQueue::UploadQueue()
	{
		command_list = std::make_shared<CommandList>(D3D12_COMMAND_LIST_TYPE_COPY);
		command_list->SetName(MakeName());

		fenceValue = -1;

		dirty = false;
		
		finished = true;
	}

	void UploadQueue::Open(uint64_t index, Ref<D3D12CommandQueue> queue)
	{
		if (!command_list->IsRecording())
		{
			command_list->Reset(index,queue);
		}
	}
	
	void UploadQueue::Upload(Ref<D3D12IUploadable> data)
	{
		m_resourcesToUpload.push_back(data);
		
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
			for each (auto& item in m_resourcesToUpload)
			{
				item->FinishedUploading();
			}
		}
	}


}
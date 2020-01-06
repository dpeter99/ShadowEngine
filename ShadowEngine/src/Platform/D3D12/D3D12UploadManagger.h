#pragma once
#include "D3D12CommandList.h"
#include "D3D12CommandQueue.h"
#include "D3D12IUploadable.h"
#include "D3D12Fence.h"

namespace ShadowEngine::Rendering::D3D12 {

	class UploadQueue {
		/**
		 * \brief The command list used for recording render commands for the graphisc command queue
		 */
		Ref<D3D12::D3D12CommandList> command_list;

		
		unsigned long long fenceValue;


		std::vector<Ref<D3D12IUploadable>> stuff;

	public:
		bool finished;

		bool dirty;

		UploadQueue();

		void Upload(Ref<D3D12IUploadable> data);

		void Execute(Ref<D3D12CommandQueue> queue, unsigned long long index);

		void Check(unsigned long long fv);
	};

	class D3D12UploadManagger {

		/**
		* \brief The Upload command queue
		*/
		Ref<D3D12::D3D12CommandQueue> command_queue;

		Ref<D3D12::D3D12Fence> fence;


		std::vector<Ref<UploadQueue>> uploadQueues;

		Ref<UploadQueue> active;

		unsigned long long index;
	public:
		D3D12UploadManagger();

		void Upload(Ref<D3D12IUploadable> data);

		void StartUpload();

		void CheckForFnishedUploads();
	};

}
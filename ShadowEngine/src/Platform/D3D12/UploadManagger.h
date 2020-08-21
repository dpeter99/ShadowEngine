#pragma once
#include "CommandList.h"
#include "D3D12CommandQueue.h"
#include "D3D12IUploadable.h"
#include "D3D12Fence.h"

namespace ShadowEngine::Rendering::D3D12 {

	class UploadQueue {
		/**
		 * \brief The command list used for recording render commands for the graphics command queue
		 */
		Ref<D3D12::CommandList> command_list;

		
		unsigned long long fenceValue;


		std::vector<Ref<D3D12IUploadable>> m_resourcesToUpload;

	public:
		bool finished;

		bool dirty;

		UploadQueue();

		void Upload(Ref<D3D12IUploadable> data);

		void Execute(Ref<D3D12CommandQueue> queue, unsigned long long index);

		void Check(unsigned long long fv);
	};

	/// <summary>
	/// Manages the upload command queue and what is being uploaded
	/// </summary>
	///
	/// This has a upload command queue and submits uploads to <see cref="UploadQueue"/>s.
	/// To upload something call <see cref="Upload"/> with a <see cref="D3D12IUploadable"/> type like <see cref="Resource"/>
	/// To submit the uploads to the command queue call <see cref="StartUpload"/>.
	class UploadManagger {

		/**
		* \brief The Upload command queue
		*/
		/// <summary>
		/// The Upload command queue this manages
		/// </summary>
		Ref<D3D12::D3D12CommandQueue> command_queue;

		/// <summary>
		/// The fence that gets triggered when a batch of uploads finishes
		/// </summary>
		Ref<D3D12::D3D12Fence> fence;

		/// <summary>
		/// A reused list of upload queues. They store the command lists
		/// </summary>
		std::vector<Ref<UploadQueue>> uploadQueues;

		/// <summary>
		/// The Upload Queue that is being recorded to
		/// </summary>
		Ref<UploadQueue> active;

		unsigned long long index;
	public:
		UploadManagger();

		/// <summary>
		/// Adds the given Uploadable to the active queue.
		/// </summary>
		/// <param name="data">The object to upload</param>
		void Upload(Ref<D3D12IUploadable> data);

		/// <summary>
		/// Starts the upload queue if it has anything to upload. Finds the new queue if needed
		/// </summary>
		void StartUpload();

		/// <summary>
		/// Checks the queue if any has finished yet
		/// </summary>
		void CheckForFnishedUploads();
	};

}
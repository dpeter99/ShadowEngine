#pragma once

#include "../Common.h"
#include "Platform/D3D12/Buffers/UploadBuffer.h"
#include "Platform/D3D12/Resource/ResourceStateTracker.h"

//#include <Platform\D3D12\D3D12CommandQueue.h>

namespace ShadowEngine::Rendering::D3D12 {

	class D3D12CommandQueue;
	
	/// <summary>
	/// Command allocators represent the render commands on the GPU side
	/// </summary>
	///
	/// Command allocators are the GPU memory that is used for storing the render commands
	/// A Command list is used to record new commands into them. A command allocators memory can be reused when all of the recorded commands finished executing.
	class CommandAllocator
	{
		com_ptr<ID3D12CommandAllocator> m_commandAllocator;


		bool free = true;
		int freeFrame = -1;
		Ref<D3D12CommandQueue> freeCommandQueue;

		D3D12_COMMAND_LIST_TYPE type;

		int id;

		//###########################
		//Dynamic Uplaod
		//###########################

		Scope<UploadBuffer> m_UploadBuffer;

		//###########################
		//Resource/Object Tracking
		//###########################

		/// <summary>
		/// Resource state tracker is used by the command list to track (per command list)
		/// the current state of a resource. The resource state tracker also tracks the
		/// global state of a resource (with it's static methods) in order to minimize resource state transitions.
		/// </summary>
		std::unique_ptr<ResourceStateTracker> m_ResourceStateTracker;

		using TrackedObjects = std::vector < Microsoft::WRL::ComPtr<ID3D12Object> >;

		/// <summary>
		/// A list of "in-flight" object to make sure they are not deleted before the command list finishes
		/// </summary>
		/// Objects that are being tracked by a command list that is "in-flight" on 
		///	the command-queue and cannot be deleted. To ensure objects are not deleted
		///	until the command list is finished executing, a reference to the object
		///	is stored. The referenced objects are released when the command list is 
		/// reset.
		TrackedObjects m_TrackedObjects;
		
	public:

		/// <summary>
		/// Standard constructor
		/// </summary>
		/// <param name="commandAllocator">The allocator that we are going to encompass</param>
		/// <param name="type">The tpe of allocator that we are holding</param>
		CommandAllocator(com_ptr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type);

		void SetName(std::wstring name);
		
		/// <summary>
		/// Returns the underlying allocator
		/// </summary>
		/// <returns>The com pointer to the allocator</returns>
		com_ptr<ID3D12CommandAllocator> const Allocator() const { return m_commandAllocator; }

		/// <summary>
		/// Returns the type of the allocator.
		/// </summary>
		/// <returns></returns>
		D3D12_COMMAND_LIST_TYPE GetType();

		int GetID() { return id; }
		

#pragma region Pooling
		//###########################
		//Pooling
		//###########################

		
		/// <summary>
		/// Checks if the given frame frees this allocator for further use
		/// </summary>
		/// <param name="frame">The frame that was last rendered</param>
		/// <returns>Weather this allocator can be reused or not</returns>
		///
		/// If the frame parameter is bigger than the frame this allocator was used in it returns true.
		bool CheckFinished(int frame, Ref<D3D12CommandQueue> queue);
		
		/// <summary>
		/// Marks the allocator as in use and sets the frame that it is used in
		/// </summary>
		/// <param name="frame">The frame that this allocator can be reused after</param>
		void MarkUsed(int frame, Ref<D3D12CommandQueue> queue);

		void SetFree();

#pragma endregion
		

		//###########################
		//Resource Tracking
		//###########################

		/// <summary>
		/// Adds a resource to the internal resources list
		/// </summary>
		/// <param name="object">The resource to be added</param>
		void TrackResource(Microsoft::WRL::ComPtr<ID3D12Object> object);

		/// <summary>
		/// Adds a resource to the internal resources list
		/// </summary>
		/// <param name="object">The resource to be added</param>
		void TrackResource(const Resource& res);

		Scope<ResourceStateTracker>& GetResourceTracker() { return m_ResourceStateTracker; }

		//###########################
		//Object tracking
		//###########################

		/// <summary>
		/// Adds an object to the tracked objects list
		/// </summary>
		/// This prevents the object form being GCd while it is used by the pipeline.
		/// <param name="object">The object to keep track of</param>
		void TrackObject(Microsoft::WRL::ComPtr<ID3D12Object> object);


		//###########################
		//Dynamic Uplaod
		//###########################

		Scope<UploadBuffer>& GetUploadBuffer() { return m_UploadBuffer; }
	};

}
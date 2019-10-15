#pragma once



namespace ShadowEngine::Rendering {
	class CommandQueue;

	class SwapChain
	{
	protected:
		float aspectRatio;
		unsigned int frameIndex;

	public:
		virtual ~SwapChain();
	public:		
		float GetAspectRatio() const { return aspectRatio; };
		virtual void SetAspectRatio() = 0;

		unsigned int GetFrameIndex() { return frameIndex; };
		virtual void SetFrameIndex() = 0;

	public:
		static Ref<SwapChain> Create(Ref<CommandQueue> commandQueue);
	};

}
#pragma once
#include "ShaderPropertySheet.h"
#include "RendererAPI.h"

namespace ShadowEngine::Rendering {

	class ConstantBufferImpl
	{
	public:
		virtual void Upload(void* data, size_t size) = 0;

		static ConstantBufferImpl* Create(size_t size);
	};
	
	class ConstantBuffer
	{
	protected:
		Ref<ConstantBufferImpl> impl;
	public:
		virtual ~ConstantBuffer() = default;

		ConstantBuffer(size_t size)
		{
			impl.reset(ConstantBufferImpl::Create(size));
		}
		
		Ref<ConstantBufferImpl> GetImpl() { return impl; };

		template <class T>
		T* As()
		{
			return data;
		}



		virtual void Set(void* d) = 0;
		virtual void Upload() = 0;
		
	};

	
	class ConstantBuffer_ShaderPropertySheet : public ConstantBuffer
	{
	protected:
		Ref<ShaderPropertySheet> data;
		size_t size;
	public:
		ConstantBuffer_ShaderPropertySheet(Ref<ShaderPropertySheet> propertySheet);


	
		void Upload() override;
		void Set(void* d) override;
	};
}

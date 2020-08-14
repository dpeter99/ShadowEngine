#pragma once

#include "RendererAPI.h"

#include <typeinfo>

namespace ShadowEngine::Rendering {

	class ConstantBufferImpl
	{
	public:
		virtual void Upload(void* data, size_t size) = 0;

		static ConstantBufferImpl* Create(size_t size, std::wstring debug_name);
	};
	
	class ConstantBuffer
	{
	protected:
		Ref<ConstantBufferImpl> impl;
	public:
		virtual ~ConstantBuffer() = default;

		ConstantBuffer(size_t size, std::wstring debug_name)
		{
			impl.reset(ConstantBufferImpl::Create(size,debug_name));
		}
		
		virtual Ref<ConstantBufferImpl> GetImpl() const { return impl; };

		/*
		template <class T>
		[[deprecated]]
		T* As()
		{
			return data;
		}
		*/


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

	template <class T>
	class ConstantBuffer_Typed : public ConstantBuffer
	{
		T data;

	public:

		ConstantBuffer_Typed(): ConstantBuffer(sizeof(T), s2ws( typeid(T).name()))
		{
			
		}
		
		T& operator=(const T& rhs) {
			data = rhs;
			return data;
		}

		T* operator->() {
			return &data;
		}

		template <class T>
		T* As ()
		{
			return data;
		}

		void Set(void* d) override
		{
			//data = (T)*d;
		}

		void Upload() override
		{
			impl->Upload(&data, sizeof(T));
		}
	};
}

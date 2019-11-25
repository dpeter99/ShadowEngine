#pragma once
#include <glm/glm.hpp>

namespace ShadowEngine::Rendering {

	class IShaderProperty : public ShadowEngine::SHObject
	{
		SHObject_Base(IShaderProperty)
	protected:
		std::string name;
	public:
		IShaderProperty(const std::string& name) :name(name) {}
		IShaderProperty() = default;

		virtual IShaderProperty* Clone() = 0;
		
		const std::string& GetName() const { return name; };

		virtual const std::string& GetPropertyTypeName() =0;
		virtual unsigned long long GetPropertyTypeSize() = 0;

		virtual void* GetPropertyData() = 0;
	};

	template<class T>
	class ShaderProperty : public IShaderProperty
	{
		SHObject_Base(ShaderProperty<T>)

			T value;

	public:
		ShaderProperty(const std::string& name) : IShaderProperty(name) {}
		ShaderProperty(const ShaderProperty& a)
		{
			this->name = a.name;
			this->value = a.value;
		}

		void SetValue(const T& data)
		{
			value = data;
		}

		IShaderProperty* Clone() override
		{
			return new ShaderProperty<T>(*this);
		}

		const std::string& GetPropertyTypeName() override
		{
			return typeid(T).name();
		}

		unsigned long long GetPropertyTypeSize() override
		{
			return  sizeof(T);
		}

		void* GetPropertyData() override
		{
			return &value;
		}
	};

	/**
	 * ShaderPropertySheet Contains the variables defined by a shader. 
	 *
	 * \brief Variables in a shader
	 *
	 * 
	 */
	class ShaderPropertySheet
	{
		/**
		 * The shader properties stored in std::unique_ptr -s as this object is the owner.
		 *
		 * \brief The shader properties
		 */
		std::vector<std::unique_ptr<IShaderProperty>> shaderProperties;

		size_t size = 0;
		void* data;
	public:
		
		/**
		 * \brief Copy constructor, makes sure the properties are copied , new ones are created
		 * \param a The Copy-from parameter
		 */
		ShaderPropertySheet(const ShaderPropertySheet& a)
		{
			for (auto& property : a.shaderProperties)
			{
				this->shaderProperties.push_back(std::unique_ptr<IShaderProperty>(property->Clone()));
			}
			this->size = a.size;
			Finalize();
		}

		ShaderPropertySheet() = default;

		/**
		 * \brief Returns the number of properties
		 * \return Num of properties
		 */
		size_t GetPropertyCount() const { return  shaderProperties.size(); }

		size_t GetSize() const { return size; }
		
		/**
		 * \brief Gets a property by index
		 * \param i The index of the needed property
		 * \return The IShaderProperty that was requested
		 */
		Scope<IShaderProperty>& GetProperty(size_t i)
		{
			return shaderProperties[i];
		}

		/**
		 * \brief Gets a property by index on const ShaderPropertySheet
		 * \param i The index of the needed property
		 * \return The IShaderProperty that was requested as const
		 */
		const Scope<IShaderProperty>& GetProperty(size_t i) const
		{
			return shaderProperties[i];
		}

		/**
		 * \brief Returns a Property by name and type
		 * \tparam T The type of the value stored in the property being requested
		 * \param name The name of the property being requested
		 * \return Pointer to the ShaderProperty<T> that was requested
		 */
		template<class T>
		ShaderProperty<T>* GetProperty(std::string name)
		{
			for (auto& property : shaderProperties)
			{
				if (property->GetTypeId() == ShaderProperty<T>::TypeId() &&
					property->GetName() == name)
				{
					return static_cast<ShaderProperty<T>*>(property.get());
				}
			}

			return nullptr;
		}

		/**
		 * \brief Returns a Property by name and type on a const ShaderPropertySheet
		 * \tparam T The type of the value stored in the property being requested
		 * \param name The name of the property being requested
		 * \return Pointer to the ShaderProperty<T> that was requested as const
		 */
		template<class T>
		ShaderProperty<T> const* GetProperty(std::string name) const
		{
			for (auto& property : shaderProperties)
			{
				if (property->GetTypeId() == ShaderProperty<T>::TypeId() &&
					property->GetName() == name)
				{
					return static_cast<ShaderProperty<T>*>(property.get());
				}
			}
		}
		
		void AddProperty(IShaderProperty* p)
		{
			shaderProperties.push_back(std::unique_ptr<IShaderProperty>(p));
			size += p->GetPropertyTypeSize();
		}

		void* Finalize()
		{
			data = malloc(size);

			size_t offset=0;
			for (int i = 0; i < this->GetPropertyCount(); ++i)
			{
				auto& prop = this->GetProperty(i);

				memcpy(((char*)data + offset), prop->GetPropertyData(), prop->GetPropertyTypeSize());
			}
			
			return data;
		}

		void* UpdataStruct()
		{
			data = malloc(size);

			size_t offset = 0;
			for (int i = 0; i < this->GetPropertyCount(); ++i)
			{
				auto& prop = this->GetProperty(i);

				memcpy(((char*)data + offset), prop->GetPropertyData(), prop->GetPropertyTypeSize());

				offset += prop->GetPropertyTypeSize();
			}

			return data;
		}

		void* GetDataStruct()
		{
			return data;
		}

		
	};


}

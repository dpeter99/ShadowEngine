#pragma once
#include <glm/glm.hpp>
#include "Core/Core.h"


namespace ShadowEngine::Rendering {

	class IShaderProperty : public ShadowEngine::SHObject
	{
		SHObject_Base(IShaderProperty)
	protected:
		std::string name;
	public:
		IShaderProperty(const std::string& name) :name(name) {}
		IShaderProperty() = default;
		virtual ~IShaderProperty() {};

		virtual IShaderProperty* Clone() = 0;

		const std::string& GetName() const { return name; };

		virtual std::string GetPropertyTypeName() = 0;
		virtual unsigned long long GetPropertyTypeSize() = 0;

		virtual void* GetPropertyData() = 0;
	};

	template<class T>
	class ShaderProperty : public IShaderProperty
	{
		SHObject_Base(ShaderProperty<T>)
	private:
		T value;

	public:
		ShaderProperty(const std::string& name) : IShaderProperty(name) {}
		ShaderProperty(const ShaderProperty& a)
		{
			this->name = a.name;
			this->value = a.value;
		}
		~ShaderProperty() override {}
		
		void SetValue(const T& data)
		{
			value = data;
		}

		IShaderProperty* Clone() override
		{
			return new ShaderProperty<T>(*this);
		}

		std::string GetPropertyTypeName() override
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

		T& GetPropertyDataTyped() {
			return value;
		}

		
	};

	//This holds a shader ptoperty that is Ref<T> to a other object
	//Usefull for non in place resources like textures
	template<class T>
	class ShaderRefProperty : public IShaderProperty
	{
		SHObject_Base(ShaderRefProperty<T>)
	private:
		Ref<T> value;

	public:
		ShaderRefProperty(const std::string& name) : IShaderProperty(name) {}
		ShaderRefProperty(const ShaderRefProperty& a)
		{
			this->name = a.name;
			this->value = a.value;
		}
		~ShaderRefProperty() override {};

		void SetValue(const Ref<T>& data)
		{
			value = data;
		}

		void SetValue(const T* data)
		{
			value.reset(data);
		}

		IShaderProperty* Clone() override
		{
			return new ShaderRefProperty<T>(*this);
		}

		std::string GetPropertyTypeName() override
		{
			return typeid(T).name();
		}

		//Returns the size of the actual type T
		unsigned long long GetPropertyTypeSize() override
		{
			return  sizeof(T);
		}

		void* GetPropertyData() override
		{
			return value.get();
		}

		T& GetPropertyDataTyped() {
			return *value;
		}

		bool IsEmpty()
		{
			return value.get() == nullptr;
		}
	};


	/**
	 * ShaderPropertySheet Contains the variables defined by a shader.
	 * This contains the actual values and the layout of the parameters
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
		std::vector<Scope<IShaderProperty>> shaderProperties;

		/**
		 * The shader properties stored in std::unique_ptr -s as this object is the owner.
		 *
		 * \brief The shader properties
		 */
		std::vector<Scope<IShaderProperty>> textures;

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

			for (auto& text : a.textures)
			{
				this->textures.push_back(std::unique_ptr<IShaderProperty>(text->Clone()));
			}

			UpdataStruct();
		}

		ShaderPropertySheet() = default;

#pragma region Properies



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

			return nullptr;
		}

		void AddProperty(IShaderProperty* p)
		{
			shaderProperties.push_back(std::unique_ptr<IShaderProperty>(p));
			size += p->GetPropertyTypeSize();
		}


#pragma endregion

		/**
		 * \brief Returns the number of textures
		 * \return Num of textures
		 */
		size_t GetTextureCount() const { return  textures.size(); }

		/**
		 * \brief Gets a property by index
		 * \param i The index of the needed property
		 * \return The IShaderProperty that was requested
		 */
		template<class T>
		ShaderRefProperty<T>* GetTexture(size_t i)
		{
			return static_cast<ShaderRefProperty<T>*>( textures[i].get());
		}

		/**
		 * \brief Gets a property by index on const ShaderPropertySheet
		 * \param i The index of the needed property
		 * \return The IShaderProperty that was requested as const
		 */
		template<class T>
		[[nodiscard]] Scope<ShaderRefProperty<T>>& GetTexture(size_t i) const
		{
			return static_cast<ShaderRefProperty<T>*>(textures[i].get());
		}

		/**
		 * \brief Gets a property by index
		 * \param i The index of the needed property
		 * \return The IShaderProperty that was requested
		 */
		Scope<IShaderProperty>& GetTexture(size_t i)
		{
			return textures[i];
		}

		/**
		 * \brief Gets a property by index on const ShaderPropertySheet
		 * \param i The index of the needed property
		 * \return The IShaderProperty that was requested as const
		 */
		const Scope<IShaderProperty>& GetTexture(size_t i) const
		{
			return textures[i];
		}


		/**
		 * \brief Returns a Property by name and type
		 * \tparam T The type of the value stored in the property being requested
		 * \param name The name of the property being requested
		 * \return Pointer to the ShaderProperty<T> that was requested
		 */
		template<class T>
		ShaderRefProperty<T>* GetTexture(std::string name)
		{
			for (auto& property : textures)
			{
				if (property->GetTypeId() == ShaderRefProperty<T>::TypeId() &&
					property->GetName() == name)
				{
					return static_cast<ShaderRefProperty<T>*>(property.get());
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
		ShaderRefProperty<T> const* GetTexture(std::string name) const
		{
			for (auto& property : textures)
			{
				if (property->GetTypeId() == ShaderRefProperty<T>::TypeId() &&
					property->GetName() == name)
				{
					return static_cast<ShaderRefProperty<T>*>(property.get());
				}
			}

			return nullptr;
		}

		template<class T>
		void AddTexture(ShaderRefProperty<T>* p)
		{
			textures.push_back(Scope<ShaderRefProperty<T>>(p));
		}

		/*
		void* Finalize[[depricated]]()
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
		*/

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



		std::string ToString()
		{
			std::string res;
			res += "Properties: \n";
			for each (auto & var in shaderProperties)
			{
				res += var->GetName();
				res += " : ";
				res += var->GetPropertyTypeName();
				res += "\n";

			}
			res += "Textures: \n";
			for each (auto & var in textures)
			{
				res += var->GetName();
				res += " : ";
				res += var->GetPropertyTypeName();
				res += "\n";

			}

			return res;
		}
	};


}

#pragma once

namespace ShadowEngine {

	class IShaderProperty : public ShadowEngine::SHObject
	{
		SHObject_Base(IShaderProperty)
	protected:
		std::string name;
	public:
		IShaderProperty(const std::string& name) :name(name) {}
		IShaderProperty() = default;

		const std::string& GetName() const { return name; };
		virtual IShaderProperty* Clone() = 0;
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
		};
	};

	class ShaderPropertySheet
	{
		std::vector<std::unique_ptr<IShaderProperty>> shaderProperties;
	public:
		ShaderPropertySheet(const ShaderPropertySheet& a)
		{
			for (auto& property : a.shaderProperties)
			{
				this->shaderProperties.push_back(std::unique_ptr<IShaderProperty>(property->Clone()));
			}
		}

		ShaderPropertySheet() = default;

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
		}

		void AddProperty(IShaderProperty* p)
		{
			shaderProperties.push_back(std::unique_ptr<IShaderProperty>(p));
		}
	};


}

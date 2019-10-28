#include <memory>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <unordered_set>

#include <vector>
#include <string>

namespace ShadowEngine {

	/**
	 * \brief This is the base class for every class in the Engine that uses runtime reflection.
	 */
	class SHObject
	{
	protected:
		/**
		 * \brief Generates a new UID for each call
		 * \return Unique ID
		 */
		static uint64_t GenerateId() noexcept
		{
			static uint64_t count = 0;
			return ++count;
		}

	public:
		/**
		 * \brief Returns the top level class type name of the object
		 * \return Class name string
		 */
		virtual const std::string& GetType() const = 0;
		/**
		 * \brief Gets the top level type ID
		 * \return UID of the class
		 */
		virtual const uint64_t GetTypeId() const = 0;

		virtual ~SHObject() = default;
	};


	/**
	 * \brief Macro to make the override functions of SHObject. This should be added in each derived class
	 * \param type The type of the class
	 */
#define SHObject_Base(type)	\
public: \
	static const std::string& Type()				{ static const std::string t = typeid(type).name(); return t; } \
	static uint64_t TypeId()						{ static const uint64_t id = GenerateId(); return id; } \
	const std::string& GetType() const override		{ return Type();  } \
	const uint64_t GetTypeId() const override		{ return  type::TypeId(); } \
private:

}

class IShaderProperty : public ShadowEngine::SHObject
{
	SHObject_Base(IShaderProperty)
protected:
		std::string name;
public:
	IShaderProperty(const std::string& name):name(name){}
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
	ShaderProperty(const std::string& name) : IShaderProperty(name){}
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
		for (auto & property : a.shaderProperties)
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
			if(property->GetTypeId() == ShaderProperty<T>::TypeId() &&
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

void main1()
{
	ShaderPropertySheet sheet;
	
	ShaderProperty<float>* shaderProperty = new ShaderProperty<float>("asd");
	shaderProperty->SetValue(23);
	sheet.AddProperty(shaderProperty);
	
	sheet.AddProperty(new ShaderProperty<bool>("asd"));
	
	auto p = sheet.GetProperty<bool>("asd");

	ShaderPropertySheet sheet_copy = sheet;

	p->SetValue(true);
	
}
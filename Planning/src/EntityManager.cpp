#include <unordered_map>
#include <typeinfo>
#include <cassert>

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

class Entity : public ShadowEngine::SHObject {
	SHObject_Base(Entity)

};

class IEntityContainer {

};

template<class T>
class EntityContainer: public IEntityContainer {
public:
	T* CreateEntityMem();
};

class EntityManager {
	using EntityContainerRegistry = std::unordered_map<int, IEntityContainer*>;
	EntityContainerRegistry m_EntityContainerRegistry;

	template<class T>
	using TComponentIterator = typename ComponentContainer<T>::iterator;

	using EntityLookupTable = std::vector<Entity*>;
	EntityLookupTable	m_ComponentLUT;
	const int COMPONENT_LUT_GROW = 5;

	template<class T>
	inline EntityContainer<T>* GetComponentContainer()
	{
		int CID = T::TypeId();

		auto it = this->m_EntityContainerRegistry.find(CID);
		EntityContainer<T>* cc = nullptr;

		if (it == this->m_EntityContainerRegistry.end())
		{
			cc = new EntityContainer<T>();
			this->m_EntityContainerRegistry[CID] = cc;
		}
		else
			cc = static_cast<EntityContainer<T>*>(it->second);

		assert(cc != nullptr && "Failed to create ComponentContainer<T>!");
		return cc;
	}

	int GetIDforComponent(Entity* component)
	{
		int i = 0;
		for (; i < this->m_ComponentLUT.size(); ++i)
		{
			if (this->m_ComponentLUT[i] == nullptr)
			{
				this->m_ComponentLUT[i] = component;
				return i;
			}
		}

		// increase component LUT size
		this->m_ComponentLUT.resize(this->m_ComponentLUT.size() + COMPONENT_LUT_GROW, nullptr);

		this->m_ComponentLUT[i] = component;
		return i;
	}

	template<class T, class ...ARGS>
	T* AddComponent(const int entityId, ARGS&&... args)
	{
		const int CTID = T::TypeId();

		// aqcuire memory for new component object of type T
		void* pObjectMemory = GetComponentContainer<T>()->CreateEntityMem();

		int componentId = this->GetIDforComponent((T*)pObjectMemory);
		//((T*)pObjectMemory)->m_ComponentID = componentId;

		// create component inplace
		Entity* component = new (pObjectMemory)T(std::forward<ARGS>(args)...);

		

		return static_cast<T*>(component);
	}
};

void main(){

}
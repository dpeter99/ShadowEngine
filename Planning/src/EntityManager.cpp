#include <unordered_map>
#include <typeinfo>
#include <cassert>
#include <iostream>

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


template<class Type>
class rtm_ptr
{
	Type* m_ptr;

	int m_uid;
	
public:
	rtm_ptr(Type* ptr) : m_ptr(ptr), m_uid(ptr->m_runtimeUID) {}

	inline Type* operator->()
	{
		if (m_ptr->m_runtimeUID != m_uid) {
			throw "Invalid Entity ref";
			return nullptr;
		}
		return m_ptr;
	}

	inline operator bool() const { return m_ptr->m_runtimeUID == m_uid; }
};

class EntityManager;

class Entity : public ShadowEngine::SHObject {
	SHObject_Base(Entity)
	
public:
	//Globally unique ID of the Entity
	//Slow to look up
	int m_runtimeUID;

	static const int INVALID_UID = -1;
	
	//Index of the Entity might be reused by others
	//Falst lookup in the LUT
	int m_runtimeIndex;

	virtual ~Entity()
	{
		
	}

	virtual void Update() {};

	template<class T>
	static void UpdateEntities(EntityManager mgr)
	{
		
	}
};

class Player: public Entity
{
	SHObject_Base(Player)
	
public:
	Player(std::string name) {  }

	virtual void Update() {
		std::cout << "Player";
	}
};

class Enemy : public Entity
{
	SHObject_Base(Enemy)

		int m_hp;
public:
	Enemy(int hp): m_hp(hp) {  }
	virtual void Update() { std::cout << "HP:"<<m_hp; }
};

class Light : public Entity
{
	SHObject_Base(Light)
public:
	Light(float intensity) {  }
};


class IEntityContainer {

};

template<class Type>
class EntityContainer: public IEntityContainer {

	static const size_t MAX_OBJECTS_IN_CHUNK = 4;
	static const size_t ALLOC_SIZE = (sizeof(Type) + alignof(Type)) * MAX_OBJECTS_IN_CHUNK;

public:

	union Element
	{
	public:
		Element* next;
		Type element;
	};
	
	class MemoryChunk
	{
		
		
	public:
		Element* chunkStart;
		Element* chunkEnd;

		int count;
		bool metadata[MAX_OBJECTS_IN_CHUNK];

		//Points to the next free element in the pool
		Element* nextFree;
		
		MemoryChunk() :count(0)
		{
			chunkStart = (Element*)malloc(ALLOC_SIZE);
			memset(chunkStart, 0, ALLOC_SIZE);
			chunkEnd = chunkStart + ALLOC_SIZE;

			for (size_t i = 1; i < MAX_OBJECTS_IN_CHUNK; i++) {
				chunkStart[i - 1].next= &chunkStart[i];
			}
			chunkStart[MAX_OBJECTS_IN_CHUNK - 1].next = nullptr;
			nextFree = chunkStart;
		}

		Type* allocate()
		{
			if (nextFree == nullptr)
				return nullptr;
			count++;
			auto res = nextFree;
			nextFree = nextFree->next;
			return (Type*)res;
		}

		void free(void* ptr)
		{
			count--;
			auto element = ((Element*)ptr);
			element->next = nextFree;
			nextFree = element;
		}
	};

protected:

	using MemoryChunks = std::list<MemoryChunk*>;
	MemoryChunks m_Chunks;
	
public:

	class iterator
	{
		typename std::list<MemoryChunk*>::iterator m_CurrentChunk;
		typename std::list<MemoryChunk*>::iterator m_EndChunk;

		Element* m_CurrentElement;
		int index;

	public:

		iterator(typename MemoryChunks::iterator begin, typename MemoryChunks::iterator end) :
			m_CurrentChunk(begin),
			m_EndChunk(end)
		{
			if (begin != end)
			{
				assert((*m_CurrentChunk) != nullptr);
				m_CurrentElement = (*m_CurrentChunk)->chunkStart;
			}
			else
			{
				m_CurrentElement = (*std::prev(m_EndChunk))->chunkEnd;
			}
		}

		inline iterator& operator++()
		{
			// move to next object in current chunk
			while (!(*m_CurrentChunk)->metadata[++index]||index!=MAX_OBJECTS_IN_CHUNK) {
				m_CurrentElement++;
			}
			

			// if we reached end of list, move to next chunk
			if (m_CurrentElement == (*m_CurrentChunk)->chunkEnd)
			{
				m_CurrentChunk++;

				if (m_CurrentChunk != m_EndChunk)
				{
					// set object iterator to begin of next chunk list
					assert((*m_CurrentChunk) != nullptr);
					m_CurrentElement = (*m_CurrentChunk)->chunkStart;
				}
			}

			return *this;
		}

		virtual inline Base& operator*() const  override { return (m_CurrentElement->element); }
		virtual inline Base* operator->() const override { return &(m_CurrentElement->element); }

		inline bool operator==(typename IEntityContainer<Base>::iterator& other) override
		{
			auto o = dynamic_cast<iterator&>(other);
			return ((this->m_CurrentChunk == o.m_CurrentChunk) && (this->m_CurrentElement == o.m_CurrentElement));
		}
		
		inline bool operator!=(typename IEntityContainer<Base>::iterator& other) override
		{
			auto o = dynamic_cast<iterator&>(other);
			return ((this->m_CurrentChunk != o.m_CurrentChunk) && (this->m_CurrentElement != o.m_CurrentElement));
		}
	};
	
	

public:

	void* CreateObject()
	{
		void* slot = nullptr;

		// get next free slot
		for (auto chunk : this->m_Chunks)
		{
			if (chunk->count > MAX_OBJECTS_IN_CHUNK)
				continue;

			slot = chunk->allocate();
			if (slot != nullptr)
			{
				//chunk->objects.push_back((OBJECT_TYPE*)slot);
				break;
			}
		}

		// all chunks are full... allocate a new one
		if (slot == nullptr)
		{
			//Allocator* allocator = new Allocator(ALLOC_SIZE, Allocate(ALLOC_SIZE, this->m_AllocatorTag), sizeof(OBJECT_TYPE), alignof(OBJECT_TYPE));
			MemoryChunk* newChunk = new MemoryChunk();

			// put new chunk in front
			this->m_Chunks.push_front(newChunk);

			slot = newChunk->allocate();

			assert(slot != nullptr && "Unable to create new object. Out of memory?!");
			//newChunk->objects.clear();
			//newChunk->objects.push_back((OBJECT_TYPE*)slot);
		}

		return slot;
	}

	void DestroyObject(void* object)
	{
		intptr_t adr = reinterpret_cast<intptr_t>(object);

		for (auto chunk : this->m_Chunks)
		{
			if (((intptr_t)chunk->chunkStart) <= adr && adr < (intptr_t)chunk->chunkEnd)
			{
				// note: no need to call d'tor since it was called already by 'delete'

				//chunk->objects.remove((OBJECT_TYPE*)object);
				chunk->free(object);
				return;
			}
		}

		assert(false && "Failed to delete object. Memory corruption?!");
	}

	
	inline typename IEntityContainer<Base>::iterator& begin() override { return iterator(this->m_Chunks.begin(), this->m_Chunks.end()); }
	inline typename IEntityContainer<Base>::iterator& end() override { return iterator(this->m_Chunks.end(), this->m_Chunks.end()); }

};

/**
 * \brief Manages the memory and IDs of Entities
 */
class EntityManager {

private:
	//Map the runtime index of the entity to the container
	using EntityContainerRegistry = std::unordered_map<int, IEntityContainer<Entity>*>;

	/**
	 * \brief Container for the Entity Containers mapped to the entity type ID
	 */
	EntityContainerRegistry m_EntityContainerRegistry;

	
	/**
	* \brief Quick access Look Up Table of active Entities
	*/
	using EntityLookupTable = std::vector<Entity*>;
	EntityLookupTable	m_EntityLUT;
	const int ENTITY_LUT_GROW = 5;

	/**
	 * \brief The next assignable Unique ID
	 */
	int nextUID = 0;

	
	/**
	 * \brief Returns the correct container for the entity type
	 * \tparam T The type of the entity
	 * \return The entity container accosted with this type
	 */
	template<class T>
	inline EntityContainer<T,Entity>* GetComponentContainer()
	{
		int CID = T::TypeId();

		auto it = this->m_EntityContainerRegistry.find(CID);
		EntityContainer<T,Entity>* cc = nullptr;

		if (it == this->m_EntityContainerRegistry.end())
		{
			cc = new EntityContainer<T,Entity>();
			this->m_EntityContainerRegistry[CID] = cc;
		}
		else
			cc = static_cast<EntityContainer<T,Entity>*>(it->second);

		assert(cc != nullptr && "Failed to create ComponentContainer<Type>!");
		return cc;
	}

	/**
	 * \brief Assigns the next free LUT index to this entity
	 * \param component 
	 * \return 
	 */
	int AssignIndexToEntity(Entity* component)
	{
		int i = 0;
		for (; i < this->m_EntityLUT.size(); ++i)
		{
			if (this->m_EntityLUT[i] == nullptr)
			{
				this->m_EntityLUT[i] = component;
				return i;
			}
		}

		// increase component LUT size
		this->m_EntityLUT.resize(this->m_EntityLUT.size() + ENTITY_LUT_GROW, nullptr);

		this->m_EntityLUT[i] = component;
		return i;
	}

	/**
	 * \brief Frees up the given index
	 * \param id 
	 */
	void ReleaseIndex(int id)
	{
		assert(id < this->m_EntityLUT.size() && "Invalid component id");
		this->m_EntityLUT[id] = nullptr;
	}
	
public:
	
	/**
	 * \brief Instantiates a new entity
	 * \tparam T Type of the Entity
	 * \tparam ARGS Constructor parameters of the Entity
	 * \param args Constructor parameters of the Entity
	 * \return 
	 */
	template<typename T, class ...ARGS>
	rtm_ptr<T> AddEntity(ARGS&&... args)
	{
		//The type ID of the Entity we are trying to add
		const int CTID = T::TypeId();

		// acquire memory for new entity object of type Type
		void* pObjectMemory = GetComponentContainer<T>()->CreateObject();

		//Assign the index and the UID to the object
		int runtimeIndex = this->AssignIndexToEntity((T*)pObjectMemory);
		((T*)pObjectMemory)->m_runtimeIndex = runtimeIndex;
		((T*)pObjectMemory)->m_runtimeUID = nextUID;
		nextUID++;

		// create Entity in place
		Entity* component = new (pObjectMemory)T(std::forward<ARGS>(args)...);

		return rtm_ptr((T*)component);
	}

	/**
	 * \brief Removes an entity
	 * \tparam T The type of the entity to remove
	 * \param entityIndex The entity index to be removed
	 */
	template<class T>
	void RemoveEntity(const int entityIndex)
	{
		//The type ID of the Entity we are trying to remove
		const int CTID = T::TypeId();

		//Lookup of the entity to be removed
		Entity* entity = this->m_EntityLUT[entityIndex];
		//Invalidate the UID
		entity->m_runtimeUID = Entity::INVALID_UID;
		// unmap entity id
		ReleaseIndex(entityIndex);
		
		assert(entity != nullptr && "FATAL: Trying to remove a entity that doesn't exsist");

		entity->~Entity();
		
		// release object memory
		GetComponentContainer<T>()->DestroyObject((void*)entity);
	}

	template<class T>
	void RemoveEntity(T* entity)
	{
		RemoveEntity<T>(entity->m_runtimeIndex);
	}

	template<class T>
	void RemoveEntity(rtm_ptr<T> entity)
	{
		RemoveEntity(entity->m_runtimeIndex);
	}

	
	template<class T>
	inline T* GetEntityByIndex(int index)
	{
		return this->m_EntityLUT[index];
	}

	void UpdateEntities()
	{
		for each (auto var in m_EntityContainerRegistry)
		{
			auto& cont = *var.second;
			for each (auto& ent in var.second)
			{
				ent.Update();
			}
		}
	}
};

void main() {
	EntityManager entity_manager;

	entity_manager.AddEntity<Player>("asd");

	auto e1 = entity_manager.AddEntity<Enemy>(20);
	auto e2 = entity_manager.AddEntity<Enemy>(20);
	auto e3 = entity_manager.AddEntity<Enemy>(20);
	auto e4 = entity_manager.AddEntity<Enemy>(20);
	auto e5 = entity_manager.AddEntity<Enemy>(20);

	entity_manager.AddEntity<Light>(10.3f);

	std::cout << "asd";



	entity_manager.RemoveEntity<Enemy>(e1->m_runtimeIndex);


	entity_manager.AddEntity<Light>(10.3f);

	if (e1)
	{
		e1->Update();
	}


	auto e6 = entity_manager.AddEntity<Enemy>(25);
	entity_manager.AddEntity<Enemy>(26);
	entity_manager.AddEntity<Enemy>(26);
	entity_manager.AddEntity<Enemy>(27);

	
	entity_manager.UpdateEntities();

	std::cout << "asd";
}
#include <unordered_map>
#include <typeinfo>
#include <cassert>
#include <iostream>
#include <functional>
#include <chrono>
#include <map>

// ReSharper disable once CppCStyleCast

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
			assert(m_ptr->m_runtimeUID == m_uid, "Wrong Object at index");
			return nullptr;
		}
		return m_ptr;
	}

	inline operator bool() const { return m_ptr->m_runtimeUID == m_uid; }

	template<class T>
	inline operator rtm_ptr<T>() const {
		return rtm_ptr<T>(m_ptr);
	}
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
	static void UpdateEntities(EntityManager* mgr)
	{
		//std::cout << std::endl;

		auto& container = *mgr->GetContainerByType<T>();

		int c = 0;

		for each (auto current in container)
		{
			//std::cout << c << typeid(T).name() << ": \t";
			current.Update();
			//std::cout << std::endl;
			c++;
		}
	}

	template<class T>
	static void RegisterDefaultUpdate(EntityManager& mgr) {
		SystemCallbacks s;
		s.update = &UpdateEntities<T>;
		
		mgr.AddSystem(s);
	}

	//virtual void RegisterUpdate_Impl() = 0;
};

class Player : public Entity
{
	SHObject_Base(Player)

		std::string m_name;
public:
	Player(std::string name):m_name(name) {  }

	virtual void Update() {
		//std::cout << "Player " << m_name;
	}
};

class Enemy : public Entity
{
	SHObject_Base(Enemy)

		int m_hp;
public:
	Enemy(int hp) : m_hp(hp) {  }
	virtual void Update() { 
		//std::cout << "HP:" << m_hp; 
	}
};

class Light : public Entity
{
	SHObject_Base(Light)
public:
	Light(float intensity) {  }
};


class IEntityContainer {
public:

	virtual void* CreateObject() = 0;


	virtual void DestroyObject(void* object) = 0;
};

template<class Type>
class EntityContainer : public IEntityContainer {

	union Element
	{
	public:
		Element* next;
		Type element;
	};

	static const size_t MAX_OBJECTS_IN_CHUNK = 2048;
	static const size_t ELEMENT_SIZE = (sizeof(Element));
	static const size_t ALLOC_SIZE = ELEMENT_SIZE * MAX_OBJECTS_IN_CHUNK;

public:

	class MemoryChunk
	{
	public:
		Element* chunkStart;
		Element* chunkEnd;

		int count;
		static const bool FreeFlag = true;
		bool metadata[MAX_OBJECTS_IN_CHUNK];

		//Points to the next free element in the pool
		Element* nextFree;

		MemoryChunk() :count(0)
		{
			chunkStart = (Element*)malloc(ALLOC_SIZE);

			memset(chunkStart, -1, ALLOC_SIZE);

			chunkEnd = &chunkStart[MAX_OBJECTS_IN_CHUNK];

			for (size_t i = 1; i < MAX_OBJECTS_IN_CHUNK; i++) {
				chunkStart[i - 1].next = &chunkStart[i];
				metadata[i] = FreeFlag;
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

			int i = ((Element*)res - (Element*)chunkStart);
			metadata[i] = !FreeFlag;

			return (Type*)res;
		}

		void free(void* ptr)
		{
			count--;
			auto element = ((Element*)ptr);
			element->next = nextFree;
			nextFree = element;

			int i = ((Element*)ptr - (Element*)chunkStart);
			metadata[i] = FreeFlag;
		}
	};

protected:

	using MemoryChunks = std::vector<MemoryChunk*>;


public:

	class iterator
	{
		typename MemoryChunks::iterator m_CurrentChunk;
		typename MemoryChunks::iterator m_EndChunk;

		Element* m_CurrentElement;
		int index;

	public:

		iterator(typename MemoryChunks::iterator begin, typename MemoryChunks::iterator end) :
			m_CurrentChunk(begin),
			m_EndChunk(end),
			index(0)
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
			m_CurrentElement = &m_CurrentElement[1];
			index++;

			while (index < MAX_OBJECTS_IN_CHUNK &&((*m_CurrentChunk)->metadata[index] == MemoryChunk::FreeFlag)) {

				m_CurrentElement = &m_CurrentElement[1];
				index++;
			}


			// if we reached end of list, move to next chunk
			if (m_CurrentElement == (*m_CurrentChunk)->chunkEnd)
			{
				m_CurrentChunk++;
				index = 0;
				if (m_CurrentChunk != m_EndChunk)
				{
					// set object iterator to begin of next chunk list
					assert((*m_CurrentChunk) != nullptr);
					m_CurrentElement = (*m_CurrentChunk)->chunkStart;
				}
			}

			return *this;
		}

		inline Type& operator*() const { return (m_CurrentElement->element); }
		inline Type* operator->() const { return &(m_CurrentElement->element); }

		inline bool operator==(typename iterator& other)
		{
			//auto o = dynamic_cast<iterator&>(other);
			return ((this->m_CurrentChunk == other.m_CurrentChunk) && (this->m_CurrentElement == other.m_CurrentElement));
		}

		inline bool operator!=(typename iterator& other)
		{
			//auto o = dynamic_cast<iterator&>(other);
			return ((this->m_CurrentChunk != other.m_CurrentChunk) && (this->m_CurrentElement != other.m_CurrentElement));
		}
	};

	MemoryChunks m_Chunks;

public:

	EntityContainer()
	{
		m_Chunks.clear();
	}

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
			this->m_Chunks.push_back(newChunk);

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


	inline iterator begin() {
		auto end = this->m_Chunks.end();
		return iterator(this->m_Chunks.begin(), end);
	}

	inline iterator end() { return iterator(this->m_Chunks.end(), this->m_Chunks.end()); }

};

struct SystemCallbacks {
	typedef void (*Callback)(EntityManager* mgr);

	Callback update;
};

/**
 * \brief Manages the memory and IDs of Entities
 */
class EntityManager {

public:
	static EntityManager* Instance;

private:
	//Map the runtime index of the entity to the container
	using EntityContainerRegistry = std::unordered_map<int, IEntityContainer*>;

	/**
	 * \brief Map of the Entity Containers mapped to the entity type ID
	 */
	EntityContainerRegistry m_EntityContainerRegistry;




	using EntityLookupTable = std::vector<Entity*>;

	/**
	 * This table is used to get a Entity by it's runtime Index.
	 * It is a fast lookup, but it is not unique. 
	 * If a Entity is freed up it's index will be given out to another Entity of the same type
	 *
	 * To use the table simply acces the element at the index of the Entity.
	 *
	 * \brief Quick access Look Up Table of active Entities
	 * 
	 */
	EntityLookupTable	m_EntityLUT;
	//Extra number of spaces to allocate in the LUT
	const int ENTITY_LUT_GROW = 2048;
	int LUTNextFree;
	bool LUTFragm = false;
	std::vector<int> LUTFragmFree;

	//using SystemUpdate = std::function<void(EntityManager*)>;
	std::vector<SystemCallbacks> systems;

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
	inline EntityContainer<T>* GetComponentContainer()
	{
		int CID = T::TypeId();

		auto it = this->m_EntityContainerRegistry.find(CID);
		EntityContainer<T>* cc = nullptr;

		if (it == this->m_EntityContainerRegistry.end())
		{
			cc = new EntityContainer<T>();
			this->m_EntityContainerRegistry[CID] = cc;

			T::RegisterDefaultUpdate<T>(*this);
		}
		else
			cc = static_cast<EntityContainer<T>*>(it->second);

		assert(cc != nullptr && "Failed to create ComponentContainer<Type>!");
		return cc;
	}

	inline IEntityContainer* GetComponentContainer(int typeID)
	{
		auto it = this->m_EntityContainerRegistry.find(typeID);
		IEntityContainer* cc = nullptr;

		if (!(it == this->m_EntityContainerRegistry.end()))
			cc = static_cast<IEntityContainer*>(it->second);

		assert(cc != nullptr && "Failed to get ComponentContainer<Type>!");
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
		if (LUTFragm) {
			i = LUTFragmFree.back();
			LUTFragmFree.pop_back();
			if (LUTFragmFree.empty()) {
				LUTFragm = false;
			}
		}
		else {
			i = LUTNextFree;
			LUTNextFree++;
			if (!(i < m_EntityLUT.size())) {
				this->m_EntityLUT.resize(this->m_EntityLUT.size() + ENTITY_LUT_GROW, nullptr);
			}
		}

		/*
		for (; i < this->m_EntityLUT.size(); ++i)
		{
			if (this->m_EntityLUT[i] == nullptr)
			{
				this->m_EntityLUT[i] = component;
				return i;
			}
		}
		*/

		// increase component LUT size
		

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

		//If this free is from the middle of the LUT
		//We record that the LUT is fragmented
		if (id != this->m_EntityLUT.size() - 1) {
			LUTFragm = true;
			LUTFragmFree.push_back(id);
		}

		this->m_EntityLUT[id] = nullptr;
	}

public:
	EntityManager() {
		Instance = this;
	}


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

	void RemoveEntity(const int entityIndex, const int typeID)
	{
		//Lookup of the entity to be removed
		Entity* entity = this->m_EntityLUT[entityIndex];
		//Invalidate the UID
		entity->m_runtimeUID = Entity::INVALID_UID;
		// unmap entity id
		ReleaseIndex(entityIndex);

		assert(entity != nullptr && "FATAL: Trying to remove a entity that doesn't exsist");

		entity->~Entity();

		// release object memory
		GetComponentContainer(typeID)->DestroyObject((void*)entity);
	}

	/**
	 * \brief Removes an entity
	 * \tparam T The type of the entity to remove
	 * \param entityIndex The entity index to be removed
	 */
	template<class T>
	void RemoveEntity(const int entityIndex)
	{
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
		RemoveEntity<T>(entity->m_runtimeIndex);
	}

	template<>
	void RemoveEntity<Entity>(rtm_ptr<Entity> entity)
	{
		RemoveEntity(entity->m_runtimeIndex,entity->GetTypeId());
	}

	template<class T>
	inline T* GetEntityByIndex(int index)
	{
		return this->m_EntityLUT[index];
	}

	template<class T>
	inline EntityContainer<T>* GetContainerByType() {
		int CID = T::TypeId();

		auto it = this->m_EntityContainerRegistry.find(CID);

		return static_cast<EntityContainer<T>*>(it->second);
	}

	void AddSystem(SystemCallbacks fn) {
		systems.push_back(fn);
	}

	void UpdateEntities()
	{
		for each (auto & var in systems)
		{
			var.update(this);
		}
	}
};

EntityManager* EntityManager::Instance = nullptr;

//Group of the entities
class Scene {

	std::list<rtm_ptr<Entity>> m_entities;

public:

	template<class T, class ...ARGS>
	rtm_ptr<T> AddEntity(ARGS&&... args) {
		rtm_ptr<T> ptr = EntityManager::Instance->AddEntity<T>(std::forward<ARGS>(args)...);
		m_entities.push_back(ptr);

		return ptr;
	}

	template<class T>
	void DestroyEntity(rtm_ptr<T>& entity) {
		EntityManager::Instance->RemoveEntity<T>(entity);
		m_entities.remove(entity);
	}

	void DestroyScene() {
		for each (auto var in m_entities)
		{
			EntityManager::Instance->RemoveEntity(var);
		}
	}
};

void main_entity() {
	EntityManager entity_manager;

	Scene s;

	auto start = std::chrono::high_resolution_clock::now();

	s.AddEntity<Enemy>(10);

	s.AddEntity<Player>("John");

	
	for (size_t i = 0; i < 50000; i++)
	{
		auto e = s.AddEntity<Enemy>(27);
		s.AddEntity<Enemy>(90);
		s.AddEntity<Light>(10);
		s.DestroyEntity(e);
		s.AddEntity<Enemy>(34);
	}
	std::cout << "Finished Scene"<<std::endl;

	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "ns\n";

	std::chrono::nanoseconds summ(0);

	for (size_t i = 0; i < 100; i++)
	{
		start = std::chrono::high_resolution_clock::now();

		for (size_t i = 0; i < 180; i++)
		{
			entity_manager.UpdateEntities();
		}

		finish = std::chrono::high_resolution_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "ns\n";
		summ += finish - start;
	}

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(summ / 200).count() << "ns\n";
	

	//s.DestroyScene();

	//e1->Update();

	

	std::cout << "asd";
}
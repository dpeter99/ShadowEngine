#pragma once
#include  "shpch.h"


/**
 * \brief This is the base class for the classes that runtime runtime reflection.
 */
class SHObject
{
protected:
	/**
	 * \brief Generates a new UID for each call
	 * \return Unique ID
	 */
	static uint64_t GenerateId()
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
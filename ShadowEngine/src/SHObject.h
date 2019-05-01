#pragma once
class SHObject
{
protected:
	static uint64_t GenerateId()
	{
		static uint64_t count = 0;
		return ++count;
	}

public:
	virtual const std::string& GetType() = 0;
	virtual const uint64_t GetTypeId() = 0;
};

#define SHObject_Base(type)	\
public: \
	static const std::string& Type() { static const std::string t = #type; return t; } \
	static uint64_t TypeId() { static const uint64_t id = GenerateId(); return id; } \
	const std::string& GetType() override { return Type();  } \
	const uint64_t GetTypeId() override { return  type::TypeId(); } \
private:
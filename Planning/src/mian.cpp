#include <list>
#include <iostream>
#include <map>

//Base Object

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
	const uint64_t GetTypeId() override { return  type::TypeId(); }



//Actual Objects

class A : public SHObject
{
SHObject_Base(A)
	
};

class B : public A
{
SHObject_Base(B)
};


//Inspector Stuff

class Inspector
{
public:
	virtual void Draw() = 0;
};

class AInspector : public Inspector
{
public:
	void Draw() override
	{
		std::cout << "A object" << std::endl;
	}

};

class BInspector : public Inspector
{
public:
	void Draw() override
	{
		std::cout << "B object" << std::endl;
	}
};

class InspecotrList{

	std::map<std::string,Inspector*> inspectors;

public:
	void Draw(SHObject& obj)
	{
		inspectors[obj.GetType()]->Draw();
	}

	void AddInspector(std::string name, Inspector* inspector)
	{
		inspectors[name] = inspector;
	}

	void Init()
	{
		AddInspector(A::Type(), new AInspector());
		AddInspector(B::Type(), new BInspector());
	}
};

//Test

void main()
{
	InspecotrList insp;
	insp.Init();

	A a_obj;
	B b_obj;

	insp.Draw(a_obj);
	insp.Draw(b_obj);
}